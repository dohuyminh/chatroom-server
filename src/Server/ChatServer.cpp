#include "ChatServer.h"
#include "../Threads/ThreadPool.h"
#include <arpa/inet.h>
#include <iostream>
#include <limits>
#include <netinet/in.h>
#include <stdexcept>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

// socket + bind
// prototype; use IPv4 cus why not
ChatServer::ChatServer(uint16_t port, size_t clientQueueSize) :
    port(port), 
    running(true),
    clientQueueSize(clientQueueSize)
{
    int re = 1, s;

    // socket  
    addrinfo hints = { 0 }, *res; 
    hints.ai_family = AF_INET;       // IPv4
    hints.ai_socktype = SOCK_STREAM; // TCP Protocol
    hints.ai_flags = AI_PASSIVE;     // Compatible with all interfaces

    s = getaddrinfo(nullptr, std::to_string(port).c_str(), &hints, &res);
    if (s != 0) {
        std::string errMsg = "Failed at getaddrinfo: ";
        errMsg += gai_strerror(s);
        throw std::runtime_error(errMsg);
    }

    sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (sockfd < 0) {
        freeaddrinfo(res);
        throw std::runtime_error("Socket initialization failed");
    }

    // bind
    // re-use port if possible
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &re, sizeof(int)) < 0) {
        throw std::runtime_error("setsockopt failed");        
    }

    if (bind(sockfd, res->ai_addr, res->ai_addrlen) < 0) {
        throw std::runtime_error("Binding socket failed");
    }

    freeaddrinfo(res);
}

// read + write + close
void ChatServer::runServer() {
    
    // listen
    if (listen(sockfd, clientQueueSize) < 0) {
        throw std::runtime_error("Listening failed");
    }

    while (running) {
        
        // accept
        sockaddr clientAddr;
        socklen_t clientAddrSize;
        int clientSockFd = accept(sockfd, &clientAddr, &clientAddrSize);
    
        if (clientSockFd < 0) {
            std::cerr << "Client acceptance failed\n";
            continue;
        }

        // handle client here
        ThreadPool::request()
            .addTask(
                std::bind(&ChatServer::handleClient, this, clientSockFd)
            );
    }

    close(sockfd);

    running = false;
}

int ChatServer::handleClient(int clientSockFd) {

    constexpr size_t BUFF_SIZE = 513;
    std::string msg;
    char buff[BUFF_SIZE] = { 0 };
    int r = 0;

    do {
        r = read(clientSockFd, buff, BUFF_SIZE - 1);
        buff[r] = 0;
        msg += buff;
    } while (r == BUFF_SIZE - 1);
    
    std::cout << "Client (" << clientSockFd << "): " << msg << '\n';

    close(clientSockFd);

    return 0;
}
