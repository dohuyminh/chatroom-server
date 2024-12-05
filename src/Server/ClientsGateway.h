#pragma once 

#include <cstddef>

namespace HTTPChatroomServer {

class __ClientsGateway {
public:
    __ClientsGateway(size_t connQueueSize);
    void setServSockFd(int servSockFd);
    void openGateway();
    void closeGateway();
    void processConnection();

private:
    void retainConnection(int clientSockFd);

private:
    size_t connQueueSize;
    int servSockFd;
};

}