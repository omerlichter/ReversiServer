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

    GameRoom(GameRoom &gameRoom);

    void joinGame(int secondPlayerSocket) ;

    int getFirstPlayerSocket() const;

    int getSecondPlayerSocket() const;

    int getStatus() const;

    string getName() const;

    pthread_t *getThread() const;

    static void *gameHandle(void *gStruct);

    void closeGameRoom(Server *server);

private:
    string name_;
    int firstPlayerSocket_;
    int secondPlayerSocket_;
    int status_;
    pthread_t *thread_;
};

typedef struct struct2 {
    GameRoom *gameRoom;
    Server *server;
} GStruct;


#endif //REVERSISERVER_GAMEROOM_H
