//
// Created by dvir on 22/12/17.
//

#include "JoinCommand.h"
#include "GameRoomsController.h"

JoinCommand::JoinCommand(Server *server) {
    this->server_ = server;
}

JoinCommand::~JoinCommand() {

}

void JoinCommand::execute(vector<string> args) {

    cout << "in start command" << endl;

    // get client socket from the args
    string clientSocketString = args.at(0);
    istringstream clientSocketStream(clientSocketString);
    int clientSocket;
    clientSocketStream >> clientSocket;

    // get the name of the new game
    string gameRoomName = args.at(1);

    GameRoomsController *gameRoomsController = GameRoomsController::getInstance();
    GameRoom *gameRoom = gameRoomsController->getFromGameRoomsMap(gameRoomName);
    if (gameRoom == NULL || gameRoom->getStatus() == 1) {
        try {
            this->server_->writeToClient(clientSocket, "-1");
        } catch (const char *message) {
            cout << message << endl;
            this->server_->closeClient(clientSocket);
            return;
        }
        this->server_->closeClient(clientSocket);
    } else {
        try {
            this->server_->writeToClient(clientSocket, "1");
        } catch (const char *message) {
            cout << message << endl;
            this->server_->closeClient(clientSocket);
            return;
        }
        gameRoom->joinGame(clientSocket);
        GStruct *gStruct = new GStruct;
        gStruct->gameRoom = gameRoom;
        gStruct->server = this->server_;
        pthread_t thraed;
        pthread_create(&thraed, NULL, gameRoom->gameHandle, (void *)gStruct);
    }
}