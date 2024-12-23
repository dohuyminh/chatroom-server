#pragma once

#include <string>
#include <unordered_map>

namespace HTTP {

class Request {
public:

    Request();
    
    // getter
    const std::string& getMethod() const;
    const std::string& getRequestURI() const;
    const std::string& getHTTPVersion() const;
    const std::string& getBody() const;
    const std::unordered_map< std::string, std::string >& getHeaders() const;

    // setter
    void setMethod(const std::string& method);
    void setRequestURI(const std::string& uri);
    void setHTTPVersion(const std::string& version);
    void setBody(const std::string& body);
    void addHeader(const std::pair< std::string, std::string >& kvp);
    void removeHeader(const std::string& key);

private:

    // Request-Line
    std::string Method;
    std::string RequestURI;
    std::string HTTPVersion;

    // general-header | request-header | entity-header 
    std::unordered_map< std::string, std::string > headers;

    // message-body
    std::string body;
};
}