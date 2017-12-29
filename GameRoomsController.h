//
// Created by dvir on 26/12/17.
//

#ifndef REVERSISERVER_GAMEROOMSCONTROLLER_H
#define REVERSISERVER_GAMEROOMSCONTROLLER_H

#include "GameRoom.h"
#include "CommandsManager.h"
#include <map>
#include <vector>
#include <iostream>

using namespace std;

class GameRoomsController {
public:
    static GameRoomsController *getInstance();

    int addToGameRoomsMap(string gameRoomName, GameRoom *gameRoom);

    int deleteFromGameRoomsMap(string gameRoomName);

    GameRoom *getFromGameRoomsMap(string gameRoomName);

    int joinToGameRoom(string gameRoomName, int playerSocket);

    vector<string> getActiveGameRoomsNames();

    void closeAllGameRooms(Server *server);

private:
    GameRoomsController() {}
    static GameRoomsController *gameRoomsController_;
    map<string, GameRoom*> gameRoomsMap_;
};


#endif //REVERSISERVER_GAMEROOMSCONTROLLER_H
