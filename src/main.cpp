#include "ChatServer.h"

int main (int argc, char *argv[]) {

    ChatServer server(8080);

    server.runServer();

    return 0;
}
