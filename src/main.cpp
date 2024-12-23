#include "Server/HTTPChatroomServer.h"

#include "absl/strings/cord_buffer.h"
#include "re2/re2.h"

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

    const auto match = RE2::FullMatch("hello", "h.*o");
    std::cout << match << '\n';

    return 0;
}

void catchSignal() {
    std::signal(SIGINT, handleSignal);
    while (ServerState::access().isRunning());
}

void handleSignal(int signum) {
    std::cout << "Server closing down...\n";
    ServerState::access().setStop();
}