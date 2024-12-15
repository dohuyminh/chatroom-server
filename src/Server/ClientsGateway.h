#pragma once 

#include <cstddef>
#include <optional>
#include <stack>

namespace HTTPChatroomServer {

class __ClientsGateway {
public:
    __ClientsGateway(size_t connQueueSize);
    void setServSockFd(int servSockFd);
    void openGateway();
    void closeGateway();
    std::optional<int> processConnection(int timeout);

private:
    void retainConnection(int clientSockFd);

private:
    size_t connQueueSize;
    int servSockFd;
};

}