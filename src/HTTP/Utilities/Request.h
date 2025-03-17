#pragma once

#include <string>
#include <unordered_map>
#include "../Constants/APIVersions.h"
#include "../Constants/Methods.h"
#include "../Constants/Paths.h"

namespace HTTP {

struct Request {
    // Request-Line
    Constants::Method   HTTPMethod;
    Constants::Version  APIVersion;
    Constants::Resource RequestTarget;
    std::unordered_map< std::string, std::string > Query;
    std::string HTTPVersion;

    // general-header | request-header | entity-header 
    std::unordered_map< std::string, std::string > Headers;

    // message-body
    std::string Body;

    Request();
};
}