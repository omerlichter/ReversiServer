//
// Created by dvir on 26/12/17.
//

#ifndef REVERSISERVER_GAMEROOMSCONTROLLER_H
#define REVERSISERVER_GAMEROOMSCONTROLLER_H

#include "GameRoom.h"
#include <map>
#include <vector>
#include <iostream>

using namespace std;

class GameRoomsController {
public:
    static GameRoomsController *getInstance();

    int addToGameRoomsMap(string gameRoomName, GameRoom *gameRoom);

    GameRoom *getFromGameRoomsMap(string gameRoomName);

    vector<string> getGameRoomsNames();

    ~GameRoomsController();

private:
    GameRoomsController() {}
    static GameRoomsController *gameRoomsController_;
    map<string, GameRoom*> gameRoomsMap_;
};


#endif //REVERSISERVER_GAMEROOMSCONTROLLER_H
