# find MongoDB driver
find_package(PkgConfig REQUIRED)

# add all the subdirectories signature for execution
add_executable(
    main
    main.cpp
    # ${SERVER_HEADERS}
    # ${SERVER_SRC}
    # ${THREADS_HEEADERS}
    # ${THREADS_SRC}
)

add_subdirectory(Server)

find_package(absl REQUIRED)
find_package(re2 REQUIRED)

target_link_libraries(
    main
    
    PRIVATE

    # 3rd party libraries
    cpp_dotenv
    re2::re2

    # source code 
    Server
)

