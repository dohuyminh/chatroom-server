cmake_minimum_required(VERSION 3.18)
project(chatroom-server)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(lib/dotenv)
# add_subdirectory(lib/abseil-cpp)
# add_subdirectory(lib/re2)
add_subdirectory(src)