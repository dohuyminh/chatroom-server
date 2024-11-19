include_directories(${chatroom-server_SOURCE_DIR}/src/Threads)

add_executable(
    main
    main.cpp
    ChatServer.h 
    ChatServer.cpp
    Threads/ThreadPool.h
    Threads/ThreadPool.cpp
)
