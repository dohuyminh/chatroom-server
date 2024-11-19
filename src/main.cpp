#include "ChatServer.h"
#include "Threads/ThreadPool.h"

int main (int argc, char *argv[]) {

    ChatServer server(8080, 100);

    ThreadPool::request().start();

    server.runServer();

    ThreadPool::request().stop();

    return 0;
}
