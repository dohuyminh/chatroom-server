# find MongoDB driver
find_package(PkgConfig REQUIRED)

# add all the subdirectories signature for execution
add_executable(
    main
    main.cpp
)

add_subdirectory(Server)
add_subdirectory(HTTP)

# find_package(absl REQUIRED)
# find_package(re2 REQUIRED)

target_link_libraries(
    main
    
    PRIVATE

    # 3rd party libraries
    cpp_dotenv

    # source code 
    Server
)

