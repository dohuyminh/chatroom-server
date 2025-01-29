#pragma once 

namespace HTTP {
namespace Constants {

    typedef short ResponseCode;

    // 2xx: Success
    constexpr ResponseCode OK = 200;
    constexpr ResponseCode CREATED = 201;
    constexpr ResponseCode NO_CONTENT = 204;

    // 4xx: Client Errors
    constexpr ResponseCode BAD_REQUEST = 400;
    constexpr ResponseCode NOT_FOUND = 404;

}
}