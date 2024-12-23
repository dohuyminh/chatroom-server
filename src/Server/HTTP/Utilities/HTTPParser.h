#pragma once

#include "Request.h"
#include <optional>

namespace HTTP {

std::optional<Request> parseRequest(const std::string& requestStr);

}