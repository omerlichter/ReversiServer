//
// Created by omer on 12/22/17.
//

#ifndef REVERSISERVER_GAMEROOM_H
#define REVERSISERVER_GAMEROOM_H

#include <string>
#include "Server.h"

using namespace std;

class GameRoom {
public:
    /**
     * constructor
     * @param firstPlayerSocket - socket id of the first player
     * @param name - name of the game room
     */
    GameRoom(int firstPlayerSocket, string name) ;

    /**
     * copy constructor
     * @param gameRoom - game room to copy from
     */
    GameRoom(GameRoom &gameRoom);

    /**
     * join second player to the game room
     * @param secondPlayerSocket - socket id of the second player
     */
    void joinGame(int secondPlayerSocket) ;

    /**
     * get function
     * @return first player socket
     */
    int getFirstPlayerSocket() const;

    /**
     * get function
     * @return second player socket
     */
    int getSecondPlayerSocket() const;

    /**
     * get function
     * @return status of the game
     */
    int getStatus() const;

    /**
     * get function
     * @return name of the game
     */
    string getName() const;

    /**
     * statuc function to run the game room
     * @param gStruct - struct that contain server and game room
     * @return nothing
     */
    static void *gameHandle(void *gStruct);

    /**
     * close the game room
     * @param server - server
     */
    void closeGameRoom(Server *server);

private:
    string name_;
    int firstPlayerSocket_;
    int secondPlayerSocket_;
    int status_;
};

// struct
typedef struct struct2 {
    GameRoom *gameRoom;
    Server *server;
} GStruct;


#endif //REVERSISERVER_GAMEROOM_H
