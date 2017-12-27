//
// Created by omer on 12/22/17.
//

#ifndef REVERSISERVER_GAMEROOM_H
#define REVERSISERVER_GAMEROOM_H

#include <string>

using namespace std;

class GameRoom {
public:
    GameRoom(int firstPlayerSocket) ;

    void joinGame(int secondPlayerSocket) ;

    int getFirstPlayerSocket() const;

    int getSecondPlayerSocket() const;

    int getStatus() const;

private:
    string name_;
    int firstPlayerSocket_;
    int secondPlayerSocket_;
    int status_;
};


#endif //REVERSISERVER_GAMEROOM_H
