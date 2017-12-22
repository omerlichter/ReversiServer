cmake_minimum_required(VERSION 3.8)
project(ReversiServer)

set(CMAKE_CXX_STANDARD 98)

set(SOURCE_FILES main.cpp Server.cpp Server.h Command.h CommandsManager.cpp CommandsManager.h GameRoom.cpp GameRoom.h)
add_executable(ReversiServer ${SOURCE_FILES})