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

private:

    int handleClient(int clientSockFd);

    uint16_t port;
    size_t clientQueueSize;
    int sockfd;
    bool running;
};
