//
// Created by dvir on 26/12/17.
//

#include "GameRoomsController.h"

pthread_mutex_t game_rooms_map_mutex;
pthread_mutex_t instance_mutex;

GameRoomsController* GameRoomsController::gameRoomsController_ = 0;

GameRoomsController* GameRoomsController::getInstance() {
    if (!gameRoomsController_) {
        pthread_mutex_lock(&instance_mutex);
        gameRoomsController_ = new GameRoomsController();
        pthread_mutex_unlock(&instance_mutex);
        return gameRoomsController_;
    } else {
        return gameRoomsController_;
    }
}

int GameRoomsController::addToGameRoomsMap(string gameRoomName, GameRoom *gameRoom) {

    pthread_mutex_lock(&game_rooms_map_mutex);
    for (map<string, GameRoom*>::iterator it = this->gameRoomsMap_.begin();
            it != this->gameRoomsMap_.end(); it++) {
        if (gameRoomName == it->first) {
            pthread_mutex_unlock(&game_rooms_map_mutex);
            return -1;
        }
    }
    this->gameRoomsMap_[gameRoomName] = gameRoom;
    pthread_mutex_unlock(&game_rooms_map_mutex);
    return 0;
}

GameRoom *GameRoomsController::getFromGameRoomsMap(string gameRoomName) {
    pthread_mutex_lock(&game_rooms_map_mutex);
    GameRoom *gameRoom = this->gameRoomsMap_[gameRoomName];
    pthread_mutex_unlock(&game_rooms_map_mutex);
    return gameRoom;
}

vector<string> GameRoomsController::getGameRoomsNames() {
    vector<string> gameRoomsNames;
    pthread_mutex_lock(&game_rooms_map_mutex);
    for (map<string, GameRoom*>::iterator it = this->gameRoomsMap_.begin();
         it != this->gameRoomsMap_.end(); it++) {
        gameRoomsNames.push_back(it->first);
    }
    pthread_mutex_unlock(&game_rooms_map_mutex);
    return gameRoomsNames;
}

GameRoomsController::~GameRoomsController() {
    for (map<string, GameRoom*>::iterator it = this->gameRoomsMap_.begin();
            it != this->gameRoomsMap_.end(); it++) {
        delete (it->second);
    }
}