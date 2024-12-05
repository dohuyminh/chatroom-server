#include "HTTPChatroomServer.h"

#include <stdexcept>
#include <sys/socket.h>
#include <unistd.h>

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

// close
void __ClientsGateway::closeGateway() {
    close(servSockFd);
}

void __ClientsGateway::processConnection() {
    
}

void __ClientsGateway::retainConnection(int clientSockFd) {

}

}