cmake_minimum_required(VERSION 3.8)
project(ReversiServer)

set(CMAKE_CXX_STANDARD 98)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

set(SOURCE_FILES main.cpp Server.cpp Server.h Command.h CommandsManager.cpp CommandsManager.h GameRoom.cpp GameRoom.h StartCommand.cpp StartCommand.h CloseCommand.cpp CloseCommand.h ListOfGamesCommand.cpp ListOfGamesCommand.h JoinCommand.cpp JoinCommand.h GameRoomsController.cpp GameRoomsController.h)
add_executable(ReversiServer ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} pthread)
