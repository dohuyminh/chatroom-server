#include "Client.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <stdexcept>

Client::Client(int clientSockFd) : clientSockFd(clientSockFd) {}

int Client::getClientSockFd() {
    return clientSockFd;
}

std::string Client::readFromClient() {
    std::string msg;
    constexpr size_t BUFF_SIZE = 513;
    char buff[BUFF_SIZE] = { 0 };
    ssize_t r = 0;

    do {
        r = recv(clientSockFd, buff, BUFF_SIZE - 1, 0);
        if (r < 0) {
            throw std::runtime_error("Reading for client with socket " + std::to_string(clientSockFd) + " unexpectedly failed");
        }
        buff[r] = 0;
        msg += buff;
    } while (r == BUFF_SIZE - 1);

    return msg;
}

void Client::sendToClient(const std::string& msg) {
    int s = send(clientSockFd, msg.c_str(), msg.size(), 0);
    if (s < 0) {
        throw std::runtime_error("Sending client with socket " + std::to_string(clientSockFd) + " unexpectedly failed");
    }
}

Client::~Client() {}