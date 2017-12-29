//
// Created by omer on 12/22/17.
//

#include "GameRoom.h"
#include "CommandsManager.h"

GameRoom::GameRoom(int firstPlayerSocket, string name) {
    this->firstPlayerSocket_ = firstPlayerSocket;
    this->name_ = name;
    this->status_ = 0;
}

GameRoom::GameRoom(GameRoom &gameRoom) {
    this->name_ = gameRoom.getName();
    this->firstPlayerSocket_ = gameRoom.getFirstPlayerSocket();
    this->secondPlayerSocket_ = gameRoom.getSecondPlayerSocket();
    this->status_ = gameRoom.getStatus();
}

void GameRoom::joinGame(int secondPlayerSocket) {
    this->secondPlayerSocket_ = secondPlayerSocket;
    this->status_ = 1;
}

int GameRoom::getFirstPlayerSocket() const {
    return this->firstPlayerSocket_;
}

int GameRoom::getSecondPlayerSocket() const {
    return this->secondPlayerSocket_;
}

string GameRoom::getName() const {
    return this->name_;
}

int GameRoom::getStatus() const {
    return this->status_;
}

pthread_t* GameRoom::getThread() const {
    this->thread_;
}

void* GameRoom::gameHandle(void *gStruct) {

    cout << "start game..." << endl;

    GStruct *gStruct1 = (GStruct*)gStruct;
    GameRoom *gameRoom = gStruct1->gameRoom;
    Server *server = gStruct1->server;

    int firstPlayerSocket = gameRoom->getFirstPlayerSocket();
    int secondPlayerSocket = gameRoom->getSecondPlayerSocket();

    // send players numbers for the clients
    try {
        server->writeToClient(firstPlayerSocket, "1");
        server->writeToClient(secondPlayerSocket, "2");
    } catch (const char *message) {
        cout << message << endl;
        // close sockets
        server->closeClient(firstPlayerSocket);
        server->closeClient(secondPlayerSocket);
        delete(gameRoom);
        pthread_exit(NULL);
    }

    // set counters
    int turnCounter = 0;
    bool end = false;

    // game loop
    while (!end) {
        if (turnCounter % 2 == 0) {
            // handle move of the first player
            string moveString;
            try {
                moveString = server->readFromClient(firstPlayerSocket);
            } catch (const char *message) {
                end = true;
                continue;
            }
            if (moveString == "END") {
                end = true;
                continue;
            }
            try {
                server->writeToClient(secondPlayerSocket, moveString);
            } catch (const char *message) {
                end = true;
                continue;
            }
        } else {
            // handle move of the second player
            string moveString;
            try {
                moveString = server->readFromClient(secondPlayerSocket);
            } catch (const char *message) {
                end = true;
                continue;
            }
            if (moveString == "END") {
                end = true;
                continue;
            }
            try {
                server->writeToClient(firstPlayerSocket, moveString);
            } catch (const char *message) {
                end = true;
                continue;
            }
        }
        turnCounter++;
    }
    cout << "end game" << endl;
    gameRoom->closeGameRoom(server);
}

void GameRoom::closeGameRoom(Server *server) {
    vector<string> args;
    args.push_back(this->getName());
    CommandsManager commandsManager(server);
    commandsManager.executeCommand("close", args);
}