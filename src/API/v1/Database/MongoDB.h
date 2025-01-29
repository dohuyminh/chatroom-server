#pragma once 
#include "DBAdapter.h"

#include <mongocxx/client.hpp>

namespace v1 {

class MongoDB : public DBAdapter {
public:
    MongoDB();

    bool create(const HTTP::Request& request) override;
    
    std::vector< std::string > query(const HTTP::Request& request) override;

    bool update(const HTTP::Request& request) override;

    bool erase(const HTTP::Request& request) override; 

private:
    mongocxx::client client;
}; 

}