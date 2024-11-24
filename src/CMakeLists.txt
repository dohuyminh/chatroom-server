# find MongoDB driver
find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBMONGOCXX REQUIRED libmongocxx)

# if any subdirectory is to be created, add them:
# file(GLOB <subdirectory name>_HEADERS "<subdirectory name>/*.h")
# file(GLOB <subdirectory name>_SRC   "<subdirectory name>/*.cpp")
file(GLOB SERVER_HEADERS "Server/*.h")
file(GLOB SERVER_SRC "Server/*.cpp")
file(GLOB CLIENT_HEADERS "Client/*.h")
file(GLOB CLIENT_SRC "Client/*.cpp")
file(GLOB THREADS_HEEADERS "Threads/*.h")
file(GLOB THREADS_SRC "Threads/*.cpp")

# add all the subdirectories signature for execution
add_executable(
    main
    main.cpp
    ${SERVER_HEADERS}
    ${SERVER_SRC}
    ${CLIENT_HEADERS}
    ${CLIENT_SRC}
    ${THREADS_HEEADERS}
    ${THREADS_SRC}
)

target_include_directories(main PRIVATE ${LIBMONGOCXX_INCLUDE_DIRS})
target_link_libraries(
    main
    PRIVATE
    cpp_dotenv
    ${LIBMONGOCXX_LIBRARIES}
)
target_compile_options(main PRIVATE ${LIBMONGOCXX_CFLAGS_OTHER})

