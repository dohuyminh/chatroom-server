#include "HTTPParser.h"

#include <regex>
#include <iostream>
#include <string_view>

namespace HTTP {

std::optional<Request> parseRequest(const std::string& requestStr) {
    // create a HTTP Request regex to check for string recognition
    // TODO: Optimize this; this is brute-force as hell
    const char* pattern = "(GET|PUT|POST|DELETE) (.*?) (HTTP/1.1)\r\n((?:.*?: .*?\r\n)*)\r\n(.*)";
    std::regex re(pattern);

    // pass the string and the pattern through a regex engine
    // TODO: Change this back to re2 later
    std::smatch piecesMatch;
    bool match = std::regex_match(requestStr, piecesMatch, re);

    // regex did not generate the given string -> reject
    if (!match) return std::nullopt;

    // validate Request-URI 

    // extract headers
    const auto headers = piecesMatch[4];

    return Request();
}

}