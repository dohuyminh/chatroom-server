#pragma once

#include <cstdint>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

class ChatServer {

public:
    ChatServer(uint16_t port);
    void runServer();

private:
    uint16_t port;
    int sockfd;
};
