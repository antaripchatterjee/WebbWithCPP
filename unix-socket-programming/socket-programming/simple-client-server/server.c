#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// C Headers for working with socket in unix
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char const *argv[])
{
    const char message[256] = "Hi! Welcome to server.";
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1)
    {
        fprintf(stderr, "Error: Could not create the socket\n");
        return EXIT_FAILURE;
    }
    
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8001);
    addr.sin_addr.s_addr = INADDR_ANY;

    if(bind(sock, (struct sockaddr*) &addr, sizeof(addr)) == -1) {
        fprintf(stderr, "Error: Could not bind the socket\n");
        close(sock);
        return EXIT_FAILURE;
    }

    if(listen(sock, 1) == -1) {
        fprintf(stderr, "Error: Could not start the listening\n");
        close(sock);
        return EXIT_FAILURE;
    }

    int client_socket;
    
    client_socket = accept(sock, NULL, NULL);
    if(client_socket == -1) {
        fprintf(stderr, "Error: Could not accept the client socket\n");
        close(sock);
        return EXIT_FAILURE;
    }
    if(send(client_socket, message, sizeof(message), 0) == -1) {
        fprintf(stderr, "Error: Could not send the message\n");
        return EXIT_FAILURE;
    }
    close(client_socket);
    close(sock);
    return EXIT_SUCCESS;
}
