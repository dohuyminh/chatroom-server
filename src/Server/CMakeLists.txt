add_library(Server "")

target_sources(
    Server 
    PRIVATE 
        ${CMAKE_CURRENT_LIST_DIR}/ChatServer.h 
        ${CMAKE_CURRENT_LIST_DIR}/ChatServer.cpp 
        ${CMAKE_CURRENT_LIST_DIR}/ClientsGateway.h
        ${CMAKE_CURRENT_LIST_DIR}/ClientsGateway.cpp
        ${CMAKE_CURRENT_LIST_DIR}/ServerState.h 
        ${CMAKE_CURRENT_LIST_DIR}/ServerState.cpp
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/HTTPChatroomServer.h
)

add_subdirectory(HTTP)
add_subdirectory(Threads)

target_link_libraries(
    Server
    PRIVATE 
        HTTP
        ThreadPool
)

target_include_directories(
    Server PUBLIC 
    ${CMAKE_CURRENT_LIST_DIR}
)