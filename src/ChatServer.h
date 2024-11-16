#pragma once

#include <cstddef>
#include <cstdint>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <string>

class ChatServer {

public:
    ChatServer(uint16_t port, size_t clientQueueSize);
    void runServer();
    void setRunning(bool running);

private:

    void displayClientMsg(int clientSockFd);
    void sendMsg(int clientSockFd);

    std::string readFromClient(int clientSockFd);
    void sendToClient(int clientSockFd, const std::string& msg);

    uint16_t port;
    size_t clientQueueSize;
    int sockfd;
    bool running;
};
