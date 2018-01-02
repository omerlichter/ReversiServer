//
// Created by dvir on 22/12/17.
//

#include "CloseCommand.h"

CloseCommand::CloseCommand(Server *server) {
    this->server_ = server;
}

void CloseCommand::execute(vector<string> args) {

    // get the name of the new game
    string gameRoomName = args.at(0);

    GameRoomsController *gameRoomsController = GameRoomsController::getInstance();
    GameRoom *gameRoom = gameRoomsController->getFromGameRoomsMap(gameRoomName);
    int firstSocket = gameRoom->getFirstPlayerSocket();
    int secondSocket = gameRoom->getSecondPlayerSocket();
    if (firstSocket != -1) {
        this->server_->closeClient(firstSocket);
    }
    if (secondSocket != -1) {
        this->server_->closeClient(secondSocket);
    }
    gameRoomsController->deleteFromGameRoomsMap(gameRoomName);
}

CloseCommand::~CloseCommand() {

}