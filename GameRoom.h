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
    GameRoom(int firstPlayerSocket, string name) ;

    void joinGame(int secondPlayerSocket) ;

    int getFirstPlayerSocket() const;

    int getSecondPlayerSocket() const;

    int getStatus() const;

    string getName() const;

    static void *gameHandle(void *gStruct);

private:
    string name_;
    int firstPlayerSocket_;
    int secondPlayerSocket_;
    int status_;
};

typedef struct struct2 {
    GameRoom *gameRoom;
    Server *server;
} GStruct;


#endif //REVERSISERVER_GAMEROOM_H
