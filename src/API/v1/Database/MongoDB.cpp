#include "MongoDB.h"
#include "dotenv.h"

#include <mongocxx/instance.hpp>
#include <mongocxx/uri.hpp>
#include <bsoncxx/json.hpp>
#include <mongocxx/exception/exception.hpp>

namespace v1 {

using bsoncxx::builder::basic::kvp;
using bsoncxx::builder::basic::make_document;

MongoDB::MongoDB() {
    mongocxx::instance instance;
    
    // reads from .env to acquire the uri
    mongocxx::uri uri(dotenv::env["MONGODB_CONNECT_STR"]);

    // create client 
    client = mongocxx::client(uri);  

    // test if MongoDB is connected successfully
    try {
        auto admin = client["admin"];
        auto cmd = make_document(kvp("ping", 1));
        auto result = admin.run_command(cmd.view());

        std::cout << bsoncxx::to_json(result) << '\n';
        std::cout << "Pinged deployment. Connection to MongoDB is successful.\n";
    } catch (const mongocxx::exception& e) {
        std::cerr << e.what() << '\n';
    }
}

bool MongoDB::create(const HTTP::Request& request) {
    if (request.HTTPMethod != HTTP::Constants::Method::POST) {
        throw std::invalid_argument("Trying to create an object instance in response to receiving an incorrect HTTP method");
    }

    
}

std::vector< std::string > query(const HTTP::Request& request) {

}

bool update(const HTTP::Request& request) {
    
}

bool erase(const HTTP::Request& request) {
    
} 

}