#pragma once

#include "Request.h"

#include <string_view>
#include <optional>

namespace HTTP {

/**
 * @brief This function is intended to receive a 
 * 
 * @param requestStr 
 * @return `std::optional< Request > 
 */
std::optional< Request > parseRequest(const std::string& requestStr);

}