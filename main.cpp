#include <iostream>
#include "Server.h"
#include "GameRoomsController.h"
#include <stdlib.h>
#include <fstream>

using namespace std;

int main() {

    // get port from file
    int port;
    ifstream inFile;
    inFile.open("setting_server.txt");
    inFile >> port;

    // create game room controller singleton
    GameRoomsController *gameRoomsController = GameRoomsController::getInstance();
    // set server
    Server server(port);
    try {
        // start the server
        server.start();
    } catch (const char *msg) {
        cout << "Cannot start server. Reason: " << msg << endl;
        server.stop();
        exit(-1);
    }

    // waiting for exit command
    string command;
    do {
        cin >> command;
    } while (command != "exit");

    // close all game rooms
    vector<string> args;
    CommandsManager commandsManager(&server);
    commandsManager.executeCommand("close_server", args);
    delete(GameRoomsController::getInstance());
}