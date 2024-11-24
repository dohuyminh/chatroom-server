#include "Server/ChatServer.h"
#include "Threads/ThreadPool.h"
#include "dotenv.h"

#include <iostream>

#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/uri.hpp>

using bsoncxx::builder::basic::kvp;
using bsoncxx::builder::basic::make_document;

using namespace dotenv;

int main (int argc, char *argv[]) {

    env.load_dotenv("../.env", false, true);

    // std::cout << env["MONGO_DB_CONNECTION_STR"] << '\n';

    ChatServer server(8080, 100);
    ThreadPool::request().start();
    server.runServer();
    ThreadPool::request().stop();

    return 0;
}
