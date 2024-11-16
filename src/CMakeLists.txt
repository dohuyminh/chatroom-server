include_directories(${chatroom-server_SOURCE_DIR}/src/client)

add_executable(
    main
    main.cpp
    ChatServer.h 
    ChatServer.cpp
    client/Client.h 
    client/Client.cpp
)
