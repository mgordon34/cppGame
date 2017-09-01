cmake_minimum_required(VERSION 3.8)

set(NETWORK_LIB
        Address.cpp
        Address.h
        common.h
        Connection.cpp
        Connection.h
        Message.cpp
        Message.h
        Socket.cpp
        Socket.h)

add_library(networkLib STATIC ${NETWORK_LIB})
