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

int GameRoomsController::deleteFromGameRoomsMap(string gameRoomName) {

    pthread_mutex_lock(&game_rooms_map_mutex);
    if (this->gameRoomsMap_.count(gameRoomName) == 0) {
        pthread_mutex_unlock(&game_rooms_map_mutex);
        return 0;
    }
    GameRoom *gameRoom = this->gameRoomsMap_[gameRoomName];
    this->gameRoomsMap_.erase(gameRoomName);
    pthread_mutex_unlock(&game_rooms_map_mutex);
    return 0;
}

GameRoom *GameRoomsController::getFromGameRoomsMap(string gameRoomName) {
    pthread_mutex_lock(&game_rooms_map_mutex);
    if (this->gameRoomsMap_.count(gameRoomName) == 0) {
        pthread_mutex_unlock(&game_rooms_map_mutex);
        throw "not game room name";
    }
    GameRoom *gameRoom = this->gameRoomsMap_[gameRoomName];
    GameRoom *instanceGameRoom = new GameRoom(*gameRoom);
    pthread_mutex_unlock(&game_rooms_map_mutex);
    return instanceGameRoom;
}

int GameRoomsController::joinToGameRoom(string gameRoomName, int playerSocket) {
    pthread_mutex_lock(&game_rooms_map_mutex);
    if (this->gameRoomsMap_.count(gameRoomName) == 0) {
        pthread_mutex_unlock(&game_rooms_map_mutex);
        return -1;
    }
    GameRoom *gameRoom = this->gameRoomsMap_[gameRoomName];
    if (gameRoom->getStatus() == 0) {
        gameRoom->joinGame(playerSocket);
    } else {
        pthread_mutex_unlock(&game_rooms_map_mutex);
        return -1;
    }
    pthread_mutex_unlock(&game_rooms_map_mutex);
    return 1;
}

vector<string> GameRoomsController::getActiveGameRoomsNames() {
    vector<string> gameRoomsNames;
    pthread_mutex_lock(&game_rooms_map_mutex);
    for (map<string, GameRoom*>::iterator it = this->gameRoomsMap_.begin();
         it != this->gameRoomsMap_.end(); it++) {
        if (it->second->getStatus() == 0) {
            gameRoomsNames.push_back(it->first);
        }
    }
    pthread_mutex_unlock(&game_rooms_map_mutex);
    return gameRoomsNames;
}

void GameRoomsController::closeAllGameRooms(Server *server) {
    for (map<string, GameRoom*>::iterator it = this->gameRoomsMap_.begin();
         it != this->gameRoomsMap_.end(); it++) {
        it->second->closeGameRoom(server);
    }
}