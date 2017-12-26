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

    // create new game room
    GameRoom gameRoom();
}


StartCommand::~StartCommand() {

}