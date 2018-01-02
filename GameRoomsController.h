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
    /**
     * static function to get the instance of the singleton
     * @return GameRoomController instance
     */
    static GameRoomsController *getInstance();

    /**
     * add game room to the map
     * @param gameRoomName - name of the game room
     * @param gameRoom - game room
     * @return -1 if the name already exist
     */
    int addToGameRoomsMap(string gameRoomName, GameRoom *gameRoom);

    /**
     * delete game room from the map
     * @param gameRoomName - name of the game room
     * @return 0
     */
    int deleteFromGameRoomsMap(string gameRoomName);

    /**
     * get game room from the map
     * @param gameRoomName - name of the game room
     * @return GameRoom
     */
    GameRoom *getFromGameRoomsMap(string gameRoomName);

    /**
     * join second player to game room in the map
     * @param gameRoomName - name of the game room
     * @param playerSocket - second player socket id
     * @return -1 if not success
     */
    int joinToGameRoom(string gameRoomName, int playerSocket);

    /**
     * get list of the active game rooms in the map
     * @return list of names of the game rooms
     */
    vector<string> getActiveGameRoomsNames();

    /**
     * close all the game rooms in the map
     * @param server - server
     */
    void closeAllGameRooms(Server *server);

private:
    GameRoomsController() {}
    static GameRoomsController *gameRoomsController_;
    map<string, GameRoom*> gameRoomsMap_;
};


#endif //REVERSISERVER_GAMEROOMSCONTROLLER_H
