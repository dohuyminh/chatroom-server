#include "Server/HTTPChatroomServer.h"

#include <thread>
#include <csignal>
#include <iostream>

using namespace HTTPChatroomServer;

void catchSignal();
void handleSignal(int signum);

int main (int argc, char *argv[]) {

    ChatServer server(8080, 100);
    
    // server thread: run the server in the background  
    std::thread serverThread(&ChatServer::runServer, &server);
    
    // signal thread (main thread): continuously check for SIGINT; stop the server if signalled 
    catchSignal();

    serverThread.join();

    return 0;
}

void catchSignal() {
    std::signal(SIGINT, handleSignal);
    while (ServerState::access().isRunning());
}

void handleSignal(int signum) {
    std::cout << "Server shutdown\n";
    ServerState::access().setStop();
}