#include "Request.h"

namespace HTTP {

Request::Request() : 
    HTTPMethod(),
    RequestTarget(), 
    APIVersion(),
    Query(), 
    Headers(), 
    Body() 
{}

}