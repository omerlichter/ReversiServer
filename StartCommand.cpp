//
// Created by dvir on 22/12/17.
//

#include "StartCommand.h"

StartCommand::StartCommand(Server *server) {
    this->server_ = server;
}

void StartCommand::execute(vector<string> args) {

    // get client socket from the args
    string clientSocketString = args.at(0);
    istringstream clientSocketStream(clientSocketString);
    int clientSocket;
    clientSocketStream >> clientSocket;

    // get the name of the new game
    string gameRoomName = args.at(1);

    // create game room
    GameRoom *gameRoom = new GameRoom(clientSocket, gameRoomName);
    GameRoomsController *gameRoomsController = GameRoomsController::getInstance();

    int status = gameRoomsController->addToGameRoomsMap(gameRoomName, gameRoom);

    if (status == 0) {
        cout << "access to open game room with name: " << gameRoomName << endl;
        try {
            this->server_->writeToClient(clientSocket, "1");
        } catch (const char *message) {
            cout << message << endl;
            this->server_->closeClient(clientSocket);
            return;
        }
    } else if (status == -1) {
        cout << "not access to open game room with name: " << gameRoomName << endl;
        try {
            this->server_->writeToClient(clientSocket, "-1");
        } catch (const char *message) {
            cout << message << endl;
            this->server_->closeClient(clientSocket);
            return;
        }
        this->server_->closeClient(clientSocket);
    }
}


StartCommand::~StartCommand() {

}