#if !defined(__WEB_HPP__)
#define __WEB_HPP__

#include <utility>
#include <queue>
#include <string>
#include <sstream>
#include <exception>

#include <aio.h>

using std::string;
using std::exception;

namespace cppweb
{
    class WebException : public exception {
        enum class Code;
        Code code;
        char* error_message;
        public:
        enum class Code {
            APPLICATION_ABORTED_BY_USER,
            SOCKERR_INIT_ERROR,
            SOCKERR_BIND_ERROR,
            SOCKERR_LISTEN_ERROR,
            SOCKERR_ACCEPT_ERROR,
            SOCKERR_SELECT_ERROR
        };

        Code get_except_code();
        char* what();
        WebException(Code code, const char* error_message);
    };

    class WebBase {
        protected:
        string name;
        virtual string getname() = 0;
        public:
        WebBase(const char* name);
    };

    class WebApp : public WebBase {
        int listening_sock;
        sockaddr_in address;
        fd_set master;
        volatile bool run;
        void init_socket(uint16_t port);
        void handle_incoming_data(int client_sock_fd, string data);
        std::queue<std::pair<aiocb*, std::ostringstream&>*> aio_client_queue;
        public:
        WebApp(const char* name);
        string getname();
        void run_forever(uint16_t port);
        void shutdown();
    };

    void abort_application(int signal_code);
} // namespace cppweb


#endif // __WEB_HPP__
