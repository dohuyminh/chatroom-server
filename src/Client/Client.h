#pragma once

#include <string>

class Client {
public:
    Client(int clientSockFd);
    int getClientSockFd();
    virtual ~Client() = 0; // mark the Client as abstract

    std::string readFromClient();
    void sendToClient(const std::string& msg);

private:
    const int clientSockFd;
};