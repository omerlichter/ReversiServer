//
// Created by dvir on 22/12/17.
//

#include "ListOfGamesCommand.h"
#include "GameRoomsController.h"

pthread_mutex_t list_of_game_mutex;

ListOfGamesCommand::ListOfGamesCommand(Server *server) {
    this->server_ = server;
}

void ListOfGamesCommand::execute(vector<string> args) {

    // get client socket from the args
    string clientSocketString = args.at(0);
    istringstream clientSocketStream(clientSocketString);
    int clientSocket;
    clientSocketStream >> clientSocket;

    GameRoomsController *gameRoomsController = GameRoomsController::getInstance();
    vector<string> gameRoomsNames = gameRoomsController->getActiveGameRoomsNames();

    for (vector<string>::iterator it = gameRoomsNames.begin();
            it != gameRoomsNames.end(); it++) {
        try {
            this->server_->writeToClient(clientSocket, *it);
        } catch (const char *message) {
            cout << message << endl;
            this->server_->closeClient(clientSocket);
            return;
        }
    }
    try {
        this->server_->writeToClient(clientSocket, "EndLoop");
    } catch (const char *message) {
        cout << message << endl;
        this->server_->closeClient(clientSocket);
        return;
    }
    this->server_->closeClient(clientSocket);
}

ListOfGamesCommand::~ListOfGamesCommand() {

}