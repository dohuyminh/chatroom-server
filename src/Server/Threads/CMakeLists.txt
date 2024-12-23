add_library(ThreadPool "")

target_sources(
    ThreadPool
    PRIVATE ${CMAKE_CURRENT_LIST_DIR}/ThreadPool.cpp
    PUBLIC  ${CMAKE_CURRENT_LIST_DIR}/ThreadPool.h
)

target_include_directories(
    ThreadPool PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)