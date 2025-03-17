#include "HTTPParser.h"

#include <iostream>
#include <re2/re2.h>

namespace HTTP {

std::optional< Request > parseRequest(const std::string& requestStr) {

    using namespace Constants;

    /*
        As per RFC 2616 https://datatracker.ietf.org/doc/html/rfc2616#section-5:
        Request           = Request-Line              
                            *(( general-header        
                            | request-header         
                            | entity-header ) CRLF)  
                            CRLF
                            [ message-body ]          
        Request-Line   = Method SP Request-URI SP HTTP-Version CRLF
        Request-URI    = "*" | absoluteURI | abs_path | authority   // for this server, only abs_path is implemented 

        Since CRUD operations are supported, POST, GET, PUT, and DELETE methods are supported.

        According to mdn web docs, the Request-URI may or may not contain a query, so this is left as optional capture group
    */
    const char* requestPattern = "(POST|GET|PUT|DELETE) /api(/v1)(/accounts)([\?](?:.+?=.+?&)*(?:.+?=.+?))? HTTP/1.1\r\n((?:.+?: .+?\r\n)*)\r\n(.*)"; 

    // std::string_view is essentially a class containing a const char* and a size_t to indicate
    // how much of a string is covered
    // this is more efficient tha simply using std::string, since std::string will actually create a 
    // seperate string, prompting to allocate new memory in heap region
    std::string_view methodView;
    std::string_view api_ver;
    std::string_view abs_path;
    std::optional< std::string_view > query;
    std::string_view headers;
    std::string_view body;

    // if the regex rejects the string -> reject 
    if (!RE2::FullMatch(requestStr, requestPattern, &methodView, &api_ver, &abs_path, &query, &headers, &body)) {
        return std::nullopt;
    }

    Method method = Method::POST;

    // C++'s std::string_view does not support switch-case, so...
    if (methodView == "POST") method = Method::POST;
    else if (methodView == "GET") method = Method::GET;
    else if (methodView == "PUT") method = Method::PUT;
    else if (methodView == "DELETE") method = Method::DELETE;
    else return std::nullopt;

    // validate Request-URI
    // check for version
    Version ver = Version::v1;
    if (api_ver == "/v1") ver = Version::v1;
    else return std::nullopt;

    // check for required resource
    Resource res = Resource::accounts;
    if (abs_path == "/accounts") res = Resource::accounts;
    else return std::nullopt;

    Request req;
    req.HTTPMethod = method;
    req.APIVersion = ver;
    req.HTTPVersion = "HTTP/1.1";
    req.RequestTarget = res;
    
    // parse query
    if (query.has_value()) {

        // skip over the question mark beginning the query string
        std::string_view q = query.value().substr(1, query.value().size() - 1);
        std::cout << q << '\n';
        std::string key;
        std::string_view value;

        while (RE2::FindAndConsume(&q, "(.+?)=(.+?)&", &key, &value)) {  
            req.Query[key] = value;
        } 
        RE2::FindAndConsume(&q, "(.+?)=(.+)", &key, &value);
        req.Query[key] = value;
    }

    // parse headers
    std::string_view key;
    std::string_view value;
    const char* kvpPattern = "(.+?): (.+?)\r\n";

    while (RE2::FindAndConsume(&headers, kvpPattern, &key, &value)) {
        req.Headers[ (std::string) key] = value;
    }

    req.Body = body;

    return req;
}

}
