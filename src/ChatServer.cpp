#include "ChatServer.h"
#include <arpa/inet.h>
#include <iostream>
#include <limits>
#include <netinet/in.h>
#include <stdexcept>
#include <string>
#include <sys/socket.h>
#include <unistd.h>

// socket + bind
// prototype; use IPv4 cus why not
ChatServer::ChatServer(uint16_t port) :
    port(port), running(true)
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
    if (listen(sockfd, 5) < 0) {
        throw std::runtime_error("Listening failed");
    }

    // accept
    // [!] TESTING OUT WITH A SINGLE CLIENT, WILL HAVE TO REWRITE ACCEPT AND SERVER LOOP
    sockaddr_in clientAddr;
    socklen_t clientAddrSize = sizeof(clientAddr);
    int clientSockFd = accept(sockfd, (sockaddr*) &clientAddr, &clientAddrSize);
    if (clientSockFd < 0) {
        throw std::runtime_error("Accept client failed");
    }

    // client details
    getpeername(clientSockFd, (sockaddr*) &clientAddr, &clientAddrSize);
    char ip[INET_ADDRSTRLEN] = { 0 };
    inet_ntop(clientAddr.sin_family, &clientAddr.sin_addr, ip, INET_ADDRSTRLEN);
    int pport = ntohs(clientAddr.sin_port);
    std::cout << "Established connection from " << ip << ": " << pport << " on socket " << clientSockFd << '\n';

    sendToClient(clientSockFd, "Connection successful"); 
    std::cout << readFromClient(clientSockFd) << '\n';
    sendToClient(clientSockFd, "Good night!");
    
    // close
    close(clientSockFd);
    close(sockfd);

    running = false;
}

std::string ChatServer::readFromClient(int clientSockFd) {
    std::string msg;
    char buff[513] = { 0 };
    
    int n = 0;
    do {
        n = read(clientSockFd, buff, 512);
        buff[n] = '\0';
        msg += buff;
    } while (n == 512);

    return msg;
}

void ChatServer::sendToClient(int clientSockFd, const std::string& msg) {
    int n = write(clientSockFd, msg.c_str(), msg.size());
    if (n < 0) {
        throw std::runtime_error("Sending message to client " + std::to_string(clientSockFd) + " failed");    
    } 
}

void ChatServer::displayClientMsg(int clientSockFd) {
    while (running) {
        std::string clientMsg = readFromClient(clientSockFd);
        if (!clientMsg.empty()) {
            std::cout << "Client: " << clientMsg << '\n';
        }
    }
}

void ChatServer::sendMsg(int clientSockFd) {
    std::string cmd;
    while (running) {
        std::cout << "ChatServer $ ";
        std::cin >> cmd; 

        // clean things up
        if (cmd == "send") {
            std::string msg;
            std::getline(std::cin, msg);
            sendToClient(clientSockFd, msg);
        }
        else if (cmd == "shutdown") {
            sendToClient(clientSockFd, "Server has shut down. Please close connection");
            running = false;
        }

        // flush the std::cin so the new command won't have any trace of tne previous ones
        std::cin.ignore(std::numeric_limits<std::streamsize>::max());
    }
}
