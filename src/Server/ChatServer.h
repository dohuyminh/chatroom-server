#pragma once 

#include "ClientsGateway.h"

#include <cstddef>
#include <cstdint>

namespace HTTPChatroomServer {

class ChatServer {
public:
    ChatServer(uint16_t port, size_t connQueueSize);
    void runServer();
    void handleClient(int clientSockFd);

private:
    __ClientsGateway connGateway;
    int sockfd;
    uint16_t port;
};

}