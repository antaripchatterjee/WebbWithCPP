#include "../includes/cppweb.hpp"

#include <iostream>

#include <cstring>
#include <cerrno>
#include <csignal>
#include <thread>

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#if !defined(BUFSIZE)
#define BUFSIZE 4096
#endif // BUFSIZE


cppweb::WebException::WebException(cppweb::WebException::Code code, const char* error_message) : code {code}, error_message {(char*) error_message} {}
cppweb::WebException::Code cppweb::WebException::get_except_code() { return code; }
char* cppweb::WebException::what() {
    return error_message;
}


cppweb::WebBase::WebBase(const char* name) : name {name} {}


cppweb::WebApp::WebApp(const char* name) : run {false}, WebBase(name) {
    signal(SIGABRT, cppweb::abort_application);
    FD_ZERO(&master);
}

string cppweb::WebApp::getname() { return name; }

void cppweb::WebApp::init_socket(uint16_t port) {
    listening_sock = socket(AF_INET, SOCK_STREAM, 0);
    if(listening_sock < 0) {
        throw WebException(
            WebException::Code::SOCKERR_INIT_ERROR,
            "Could not initialize the socket"
        );
    }
    
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    address.sin_addr.s_addr = INADDR_ANY;

    if(bind(listening_sock, reinterpret_cast<sockaddr*>(&address), sizeof (address)) < 0) {
        close(listening_sock);
        throw WebException(
            WebException::Code::SOCKERR_BIND_ERROR,
            "Could not the bind the socket"
        );
    }

    if(listen(listening_sock, SOMAXCONN) < 0) {
        close(listening_sock);
        throw WebException(
            WebException::Code::SOCKERR_LISTEN_ERROR,
            "Could not start the listening of the incoming sockets"
        );
    }
    FD_SET(listening_sock, &master);
    run = true;
}

void cppweb::WebApp::run_forever(uint16_t port) {
    init_socket(port);
    std::thread socket_selector([](WebApp* app){
        int __i = 0;
        timeval timeout = {
            .tv_sec = 5,
            .tv_usec = 0
        };
        while(app->run) {
            fd_set read_sockets = app->master;
            int __select_count = select(0, &read_sockets, nullptr, nullptr, &timeout);
            if(__select_count < 0) {
                __i++;
                if(__i == 1024) {
                    for(int sock = 0; sock < FD_SETSIZE; sock++) {
                        if(FD_ISSET(sock, &(app->master))) {
                            close(sock);
                        }
                    }
                    throw WebException(
                        WebException::Code::SOCKERR_SELECT_ERROR,
                        "Could not run function `select` for multiple times(1024)"
                    );
                }
                continue;
            } else {
                __i = 0;
                if(__select_count == 0) {
                    continue;
                    // Handle timeout issue
                }
            }
            for(int sock = 0; sock < FD_SETSIZE; sock++) {
                if(FD_ISSET(sock, &read_sockets)) {
                    if(sock == app->listening_sock) {
                        // Accept a new connection
                        sockaddr_in client_address;
                        socklen_t client_addr_len = sizeof(client_address);
                        int client_socket = accept(
                            app->listening_sock,
                            (sockaddr*)&client_address,
                            &client_addr_len
                        );
                        if(client_socket >= 0) {
                            FD_SET(client_socket, &(app->master));
                        } else {
                            fputs("Could not accept a client\n", stderr);
                        }
                    } else {
                        // Receive the message
                        aiocb* _client = new aiocb;
                        _client->aio_buf = static_cast<volatile void*>(new char[BUFSIZE+1]{ 0 });
                        _client->aio_fildes = sock;
                        _client->aio_nbytes = BUFSIZE;
                        _client->aio_offset = 0;
                        std::ostringstream oss;
                        std::pair<aiocb*, std::ostringstream&> aio_client(_client, oss);
                        app->aio_client_queue.push(&aio_client);
                    }
                }
            }
        }
    }, this);
    while(run) {
        while(!aio_client_queue.empty()) {
            std::pair<aiocb*, std::ostringstream&>* aio_client = aio_client_queue.back();
            // aiocb* aio_client->first = aio_client->first;
            aio_client_queue.pop();
            int result = aio_read(aio_client->first);
            if(result < 0) {
                // Handle read error
            } else {
                while(aio_error(aio_client->first) == EINPROGRESS);
                aio_client->second << static_cast<volatile char*>(aio_client->first->aio_buf);
                int ret = aio_return(aio_client->first);
                if(ret > 0) {
                    aio_client_queue.push(aio_client);
                    aio_client->first->aio_offset += BUFSIZE;
                    memset((void*)(aio_client->first->aio_buf), 0, BUFSIZE+1);
                } else if(ret == 0) {
                    int client_fd = aio_client->first->aio_fildes;
                    delete aio_client->first->aio_buf;
                    delete aio_client->first;
                    handle_incoming_data(client_fd, aio_client->second.str());
                    aio_client->second.clear();
                }
            }  
        }
    }
}

void cppweb::WebApp::shutdown() {
    run = false;
}

void cppweb::WebApp::handle_incoming_data(int client_sock_fd, string data) {
    std::cout << "SOCKET #" << client_sock_fd << ": " << data << std::endl;
}


void cppweb::abort_application(int signal_code) {
    std::ostringstream oss;
    oss << "SIGABRT (" << signal_code << ") received";
    throw WebException(
        WebException::Code::APPLICATION_ABORTED_BY_USER,
        oss.str().c_str()
    );
}