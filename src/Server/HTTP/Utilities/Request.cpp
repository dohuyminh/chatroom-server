#include "Request.h"

namespace HTTP {

Request::Request() : 
    Method(), 
    RequestURI(), 
    HTTPVersion(),
    headers(), 
    body() {}

// getter
const std::string& Request::getMethod() const {
    return Method;
}
const std::string& Request::getRequestURI() const {
    return RequestURI;
}
const std::string& Request::getHTTPVersion() const {
    return HTTPVersion;
}
const std::string& Request::getBody() const {
    return body;
}
const std::unordered_map< std::string, std::string >& Request::getHeaders() const {
    return headers;
}

// setter
void Request::setMethod(const std::string& method) {
    Method = method;
}
void Request::setRequestURI(const std::string& uri) {
    RequestURI = uri;
}
void Request::setHTTPVersion(const std::string& version) {
    HTTPVersion = version;
}
void Request::setBody(const std::string& body) {
    this->body = body;
}
void Request::addHeader(const std::pair< std::string, std::string >& kvp) {
    headers.insert(kvp);
}
void Request::removeHeader(const std::string& key) {
    headers.erase(key);
}

}