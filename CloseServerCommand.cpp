//
// Created by omer on 12/29/17.
//

#include "CloseServerCommand.h"

CloseServerCommand::CloseServerCommand(Server *server) {
    this->server_ = server;
}

void CloseServerCommand::execute(vector<string> args) {

    GameRoomsController *gameRoomsController = GameRoomsController::getInstance();
    gameRoomsController->closeAllGameRooms(this->server_);
    this->server_->stop();
}

CloseServerCommand::~CloseServerCommand() {

}