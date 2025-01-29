add_library(API "")

target_sources(
    API 
    PRIVATE
        
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/V1.h
)

target_link_libraries(
    API 
    PRIVATE
        HTTP
)

target_include_directories(
    API
    PUBLIC 
        ${CMAKE_CURRENT_LIST_DIR}   
)