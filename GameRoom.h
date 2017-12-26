//
// Created by omer on 12/22/17.
//

#ifndef REVERSISERVER_GAMEROOM_H
#define REVERSISERVER_GAMEROOM_H

#include <string>

using namespace std;

class GameRoom {
public:
    GameRoom(string name, int firstPlayerSocket) ;
    void joinGame(int secondPlayerSocket) ;

    const string &getName() const;

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
