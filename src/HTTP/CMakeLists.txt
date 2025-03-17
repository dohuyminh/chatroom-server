add_library(HTTP "")

target_sources(
    HTTP
    PRIVATE 
        ${CMAKE_CURRENT_LIST_DIR}/Utilities/HTTPParser.cpp
        ${CMAKE_CURRENT_LIST_DIR}/Utilities/Request.cpp
    PUBLIC  ${CMAKE_CURRENT_LIST_DIR}/HTTP.h
)

find_package(absl REQUIRED)
find_package(re2  REQUIRED)

target_link_libraries(
    HTTP 
        PRIVATE re2::re2   
)

target_include_directories(
    HTTP PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)
