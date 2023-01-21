#include <stdio.h>
#include <stdlib.h>

// C Headers for working with socket in unix
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>


int main(int argc, const char* argv[]) {
    int sock;
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock == -1) {
        fprintf(stderr, "Error: Could not create the socket\n");
        return EXIT_FAILURE;
    }
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8001);
    addr.sin_addr.s_addr = INADDR_ANY;

    int connection_status = connect(sock, (struct sockaddr*) &addr, sizeof(addr));
    if(connection_status == -1) {
        fprintf(stderr, "Error: Could not connect to the server\n");
        close(sock);
        return EXIT_FAILURE;
    }
    
    char buffer[256] = { 0 };
    if(recv(sock, &buffer, sizeof(buffer), 0) != -1) {
        fprintf(stdout, "Message:\n%s\n", buffer);
        close(sock);
    } else {
        fprintf(stderr, "Could not read the input buffer.\n");
        close(sock);
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}