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

        ThreadPool::request().addTask(std::bind(&ChatServer::handleClient, this, client));
    }

    // close the server (close)
    connGateway.closeGateway();

    // close thread pool when server closes
    ThreadPool::request().stop();

}

void ChatServer::handleClient(int clientSockFd) {

    if (clientSockFd == -1) return;

    // a 512KB buffer to store each request
    constexpr size_t requestBuffSize = 65537;
    char requestBuff[ requestBuffSize ] = { 0 };

    // HTTP/1.1 supports pipelining; got to implement that
    bool connDone = false;
    while (!connDone) {

        // read HTTP requst
        ssize_t readBytes = read(clientSockFd, requestBuff, requestBuffSize);
        
        // error reading; closing connection
        if (readBytes == -1) {
            std::cerr << "Reading request from client " << clientSockFd << " failed\n";
            break;
        } 
        
        // client has closed connection; closing now
        else if (readBytes == 0) { break; }

        // if the client's request is bigger than 512KB, send response with status 413
        else if (readBytes == requestBuffSize) {
            
        }

        // parse HTTP reqest
        std::optional< HTTP::Request > extract = HTTP::parseRequest(requestBuff);

        if (!extract.has_value()) {
            std::string response = "HTTP/1.1 400 Bad Request\r\nContent-Type: application/json\r\nContent-Length: 19\r\n\r\n{\n\t\"lmao\": \"yeet\"\n}";
            if (write(clientSockFd, response.c_str(), response.size()) == -1) {
                std::cerr << "Sending response to client " << clientSockFd << " failed\n";
            }
            continue;
        }

        HTTP::Request& request = extract.value(); 
        
        // execute request
        // send request to the API         

        // the client is now done; closing socket 
        if (request.Headers.count("Connection") && request.Headers["Connection"] == "close") {
            break;
        }
    }

    // close client's connection
    if (close(clientSockFd) == -1) {
        std::cerr << "close\n";
    }
    
}

}

