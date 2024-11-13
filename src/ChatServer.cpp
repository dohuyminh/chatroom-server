#include "ChatServer.h"
#include <iostream>
#include <stdexcept>
#include <string>

// socket + bind
// prototype; use IPv4 cus why not
ChatServer::ChatServer(uint16_t port) :
    port(port), serveraddr({0})
{
    int re = 1, s;

    // socket  
    addrinfo hints = { 0 }, *res; 
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

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
    
    std::cout << "Server is now running on port: " << port << '\n';

    bool running = true;
    
    // command interface; interacting with the server
    std::string cmd;

    while (running) {

        std::cout << "cmd: ";
        std::cin >> cmd;
        
        if (cmd == "shutdown") {
            running = false;
        }

    }
    
    
}
