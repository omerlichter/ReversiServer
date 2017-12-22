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

    const string &getName_() const;

    int getFirstPlayerSocket_() const;

    int getSecondPlayerSocket_() const;

private:
    string name_;
    int firstPlayerSocket_;
    int secondPlayerSocket_;
};


#endif //REVERSISERVER_GAMEROOM_H
