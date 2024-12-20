#pragma once

#include <string>
#include <unordered_set>
#include <optional>
#include <utility>

#include "../HTTP/HTTP.h"

namespace DB {

typedef std::pair< HTTP::ResponseCode, std::optional<std::string> > Response;

class DBAdapter {
public:

    // POST 
    virtual Response POST(const std::string& gate, const std::string& content) = 0;

    // GET 
    virtual Response GET(const std::string& gate, const std::string& content) = 0;

    // PUT 
    virtual Response PUT(const std::string& gate, const std::string& content) = 0;

    // DELETE
    virtual Response DELETE(const std::string& gate, const std::string& content) = 0;
};

}
