cmake_minimum_required(VERSION 3.8)
project(cppGame)

set(CMAKE_CXX_STANDARD 11)

set(NETWORK_FILES
        Network/Address.cpp
        Network/Address.h
        Network/common.h
        Network/Connection.cpp
        Network/Connection.h
        Network/Message.cpp
        Network/Message.h
        Network/Socket.cpp
        Network/Socket.h)

set(SOURCE_FILES
        Server/entity.cpp
        Server/entity.h
        Server/Player.cpp
        Server/Player.h
        Server/Server.cpp
        Server/Server.h
        Server/sv_main.cpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(./Dependencies/include)
link_directories(./Dependencies/lib)

add_subdirectory(MattEngine)
add_subdirectory(Game)
add_subdirectory(Network)
add_subdirectory(Server)
