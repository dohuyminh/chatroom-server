#include "MongoDBGateway.h"

namespace DB {

MongoDBGateway::MongoDBGateway() : instance() {
    // load credentials from .env
    
}

Response MongoDBGateway::POST(const std::string& gate, const std::string& content) {
    auto chatdb = client["chatdb"];
    
}

Response MongoDBGateway::GET(const std::string& gate, const std::string& content) {
    auto chatdb = client["chatdb"];
}

Response MongoDBGateway::PUT(const std::string& gate, const std::string& content) {
    auto chatdb = client["chatdb"];
}

Response MongoDBGateway::DELETE(const std::string& gate, const std::string& content) {
    auto chatdb = client["chatdb"];
}

}