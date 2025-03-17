#include "HTTPChatroomServer.h"

#include <stdexcept>
#include <sys/socket.h>
#include <unistd.h>
#include <poll.h>

namespace HTTPChatroomServer {

__ClientsGateway::__ClientsGateway(size_t connQueueSize) : 
    connQueueSize(connQueueSize), 
    servSockFd(-1)
{}

void __ClientsGateway::setServSockFd(int servSockFd) {
    this->servSockFd = servSockFd;
}

// listen 
void __ClientsGateway::openGateway() {
    if (servSockFd == -1) {
        throw std::invalid_argument("Server's Socket File Descriptor has not been specified.");
    }
    if (listen(servSockFd, connQueueSize) < 0) {
        throw std::runtime_error("Listening on specified Server's Socket File Descriptor failed");
    }
}

// accept


// close
void __ClientsGateway::closeGateway() {
    close(servSockFd);
}

std::optional<int> __ClientsGateway::processConnection(int timeout) {
    
    pollfd p = { 0 };
    p.fd = servSockFd;
    p.events = POLLIN;

    int nEvents = poll(&p, 1, timeout);
    if (nEvents == 0 || !(p.revents & POLLIN)) { return std::nullopt; }

    sockaddr addr;
    socklen_t addrSize = sizeof(addr);
    int clientFd = accept(servSockFd, &addr, &addrSize);
    if (clientFd < 0) {
        throw std::runtime_error("Accepting client failed");
    }

    return clientFd;
    
}

void __ClientsGateway::retainConnection(int clientSockFd) {

}

}