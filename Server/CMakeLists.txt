cmake_minimum_required(VERSION 3.8)

set(SOURCE_FILES
        entity.cpp
        entity.h
        Player.cpp
        Player.h
        Server.cpp
        Server.h
        sv_main.cpp)

add_executable(server ${SOURCE_FILES})
target_link_libraries(server networkLib)
