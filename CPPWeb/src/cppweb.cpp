#include <winsock2.h>
#include "../includes/cppweb.hpp"

cppweb::Application::Application(string name) : Base(name) {}

string cppweb::Application::getName() {
    return name;
}

cppweb::AppStatus cppweb::Application::runForever(const char* hostname, int port) {
    WSADATA wsa;
    if(WSAStartup(MAKEWORD(2, 2), &wsa) !=0) {
        return AppStatus::CPPWEB_WSASTARTUP_ERROR;
    }
    SOCKET s = socket(AF_INET, SOCK_STREAM, 0);
    if(s == INVALID_SOCKET) {
        return AppStatus::CPPWEB_INVALID_SOCKET_ERROR;
    }
    
}