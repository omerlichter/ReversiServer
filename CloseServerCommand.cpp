//
// Created by omer on 12/29/17.
//

#include "CloseServerCommand.h"
#include "GameRoomsController.h"

CloseServerCommand::CloseServerCommand(Server *server) {
    this->server_ = server;
}

void CloseServerCommand::execute(vector<string> args) {

    // get the name of the new game
    string gameRoomName = args.at(0);

    GameRoomsController *gameRoomsController = GameRoomsController::getInstance();
    gameRoomsController->closeAllGameRooms(this->server_);
    delete(gameRoomsController);
}

CloseServerCommand::~CloseServerCommand() {

}