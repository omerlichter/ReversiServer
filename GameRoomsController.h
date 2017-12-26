//
// Created by dvir on 26/12/17.
//

#ifndef REVERSISERVER_GAMEROOMSCONTROLLER_H
#define REVERSISERVER_GAMEROOMSCONTROLLER_H

#include "GameRoom.h"
#include <map>
#include <iostream>

using namespace std;

class GameRoomsController {
public:
    static GameRoomsController *getInstance();

    void addToGameRoomsMap(GameRoom gameRoom);

    GameRoom &getFromGameRoomsMap(string &gameRoomName);

private:
    GameRoomsController() {}
    static GameRoomsController *gameRoomsController_;
    map<string, GameRoom> *gameRoomsMap_;
};


#endif //REVERSISERVER_GAMEROOMSCONTROLLER_H
