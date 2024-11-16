#pragma once

#include <string>

class Client {
public:
    Client(int clientSockFd);    
    int getClientSockFd();
    std::string getMessage();
    void sendToClient(const std::string& msg);

private:
    int clientSockFd;
    bool isClosed;
};
