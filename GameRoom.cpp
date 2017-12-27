//
// Created by omer on 12/22/17.
//

#include "GameRoom.h"

GameRoom::GameRoom(int firstPlayerSocket) {
    this->firstPlayerSocket_ = firstPlayerSocket;
    this->status_ = 0;
}

void GameRoom::joinGame(int secondPlayerSocket) {
    this->secondPlayerSocket_ = secondPlayerSocket;
    this->status_ = 1;
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
