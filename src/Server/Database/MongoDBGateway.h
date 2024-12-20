#pragma once

#include "DBAdapter.h"

#include <mongocxx/instance.hpp>
#include <mongocxx/client.hpp>

namespace DB {

class MongoDBGateway : public DBAdapter {
public:

    MongoDBGateway();

    Response POST(const std::string& gate, const std::string& content) override;
    
    Response GET(const std::string& gate, const std::string& content) override;

    Response PUT(const std::string& gate, const std::string& content) override;

    Response DELETE(const std::string& gate, const std::string& content) override;

private:
    mongocxx::instance instance;
    mongocxx::client client;
};

}
