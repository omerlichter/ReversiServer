//
// Created by dvir on 26/12/17.
//

#include "GameRoomsController.h"

GameRoomsController* GameRoomsController::gameRoomsController_ = 0;

GameRoomsController* GameRoomsController::getInstance() {
    if (!gameRoomsController_) {
        gameRoomsController_ = new GameRoomsController();
        return gameRoomsController_;
    } else {
        return gameRoomsController_;
    }
}

void GameRoomsController::addToGameRoomsMap(GameRoom gameRoom) {
    this->gameRoomsMap_[""] = gameRoom;
}

void GameRoomsController::getFromGameRoomsMap(string gameRoomName) {

}