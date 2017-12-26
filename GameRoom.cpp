//
// Created by omer on 12/22/17.
//

#include "GameRoom.h"

GameRoom::GameRoom(string name, int firstPlayerSocket) {
    this->name_ = name;
    this->firstPlayerSocket_ = firstPlayerSocket;
    this->status_ = 0;
}

void GameRoom::joinGame(int secondPlayerSocket) {
    this->secondPlayerSocket_ = secondPlayerSocket;
}

const string &GameRoom::getName() const {
    return this->name_;
}

int GameRoom::getFirstPlayerSocket() const {
    return this->firstPlayerSocket_;
}

int GameRoom::getSecondPlayerSocket() const {
    return this->secondPlayerSocket_;
}

int GameRoom::getStatus() const {
    return this->status_;
}
