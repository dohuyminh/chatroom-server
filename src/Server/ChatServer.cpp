#include "ChatServer.h"
#include "ServerState.h"
#include "ThreadPool.h"
#include "HTTP.h"

#include <arpa/inet.h>
#include <iostream>
#include <netinet/in.h>
#include <stdexcept>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

namespace HTTPChatroomServer {

// socket + bind
// prototype; use IPv4 cus why not
ChatServer::ChatServer(uint16_t port, size_t connQueueSize) : 
    connGateway(__ClientsGateway(connQueueSize)), 
    port(port)
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
    connGateway.setServSockFd(sockfd);
}

// listen + read + write + close
void ChatServer::runServer() {

    // open server
    ServerState::access().setRunning();

    // open thread pool to execute task
    ThreadPool::request().start();
    
    // open the server for client (listen)
    connGateway.openGateway();

    std::cout << "Server is now listening on port: " << port << '\n';

    // main loop for gateway to handle connection
    while (ServerState::access().isRunning()) {

        std::optional<int> clientSockFd;
        try {
            clientSockFd = connGateway.processConnection(1000);
        } catch (std::runtime_error const&) { 
            continue;
        }
        
        int client = clientSockFd.value_or(-1);
        auto stuff = [client]() {
            if (client == -1) return;
            
            std::string msg;

            // allocate 512KB for reading request
            constexpr ssize_t BUFFSIZE = 65536;
            char buff [ BUFFSIZE ] = { 0 };
            ssize_t r = read(client, buff, BUFFSIZE - 1);

            if (r <= 0) {
                close(client);
                return;
            }

            buff[r] = 0;
            msg += buff;

            std::cout << "Client (" << client << "):\n";
            std::cout << msg << '\n';
            auto lmao = HTTP::parseRequest(msg);

            close(client);
        };

        ThreadPool::request().addTask(stuff);
    }

    // close the server (close)
    connGateway.closeGateway();

    // close thread pool when server closes
    ThreadPool::request().stop();

}

void ChatServer::handleClient(int clientSockFd) {

    // a 512KB buffer to store each request
    constexpr size_t requestBuffSize = 65536;
    char requestBuff[ requestBuffSize ] = { 0 };

    // HTTP/1.1 supports pipelining; got to implement that
    bool connDone = false;
    while (!connDone) {

        // read HTTP requst
        
        ssize_t readBytes = read(clientSockFd, requestBuff, requestBuffSize - 1);
        // error reading; closing connection
        if (readBytes == -1) {
            std::cerr << "Reading request from client " << clientSockFd << " failed\n";
            break;
        } 
        // client has closed connection; closing now
        else if (readBytes == 0) { break; }

        // parse HTTP reqest
        // HTTP::Request request = HTTP::parseRequest(requestBuff);

        // execute request

        // send response to client 

    }

    // close client's connection
    if (close(clientSockFd) == -1) {
        std::cerr << "close\n";
    }
    
}

}

