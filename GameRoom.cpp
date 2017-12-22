//
// Created by omer on 12/22/17.
//

#include "GameRoom.h"

GameRoom::GameRoom(string name, int firstPlayerSocket) {
    this->name_ = name;
    this->firstPlayerSocket_ = firstPlayerSocket;
}

void GameRoom::joinGame(int secondPlayerSocket) {
    this->secondPlayerSocket_ = secondPlayerSocket;
}

const string &GameRoom::getName_() const {
    return name_;
}

int GameRoom::getFirstPlayerSocket_() const {
    return firstPlayerSocket_;
}

int GameRoom::getSecondPlayerSocket_() const {
    return secondPlayerSocket_;
}
