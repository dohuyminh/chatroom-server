#include "Client.h"
#include <cstddef>
#include <netinet/in.h>
#include <stdexcept>
#include <string>
#include <sys/socket.h>
#include <unistd.h>

constexpr size_t MAX_BUFF = 513;

Client::Client(int clientSockFd) 
    : clientSockFd(clientSockFd)
{}

int Client::getClientSockFd() {
    return clientSockFd;
}

std::string Client::getMessage() {
    std::string res;
    char buff[MAX_BUFF] = { 0 };
    int r = 0;

    do {
        r = read(clientSockFd, buff, MAX_BUFF - 1);
        buff[r] = '\0';
        res += buff;
    } while (r == MAX_BUFF - 1);

    return res;
}

void Client::sendToClient(const std::string& msg) {
    int s = send(clientSockFd, msg.c_str(), msg.size(), 0);
    if (s < 0) {
        throw std::runtime_error("Sending message to client with socket " + std::to_string(clientSockFd) + " failed");
    }
}
