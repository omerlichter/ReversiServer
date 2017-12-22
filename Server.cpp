#include "Server.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <stdio.h>

using namespace std;

#define MAX_CONNECTED_CLIENTS 2
#define BUFFER_SIZE 10

Server::Server(int port): port_(port), serverSocket_(0) {
    this->commandsManager_ = CommandsManager();
    cout << "Server" << endl;
}

void Server::start() {

    // Create a socket point
    this->serverSocket_ = socket(AF_INET, SOCK_STREAM, 0);
    if (this->serverSocket_ == -1) {
        throw "Error opening socket";
    }

    // Assign a local address to the socket
    struct sockaddr_in serverAddress;
    bzero((void *)&serverAddress, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(this->port_);
    if (bind(this->serverSocket_, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1) {
        throw "Error on binding";
    }

    // Start listening to incoming connections
    listen(this->serverSocket_, MAX_CONNECTED_CLIENTS);

    // Define the client socket's structures
    struct sockaddr_in firstClientAddress;
    socklen_t firstClientAddressLen = sizeof((struct sockaddr *)&firstClientAddress);
    struct sockaddr_in secondClientAddress;
    socklen_t secondClientAddressLen = sizeof((struct sockaddr *)&secondClientAddress);

    //
    while (true) {
        cout << "Waiting for first player to connect..." << endl;
        // Accept a new client connection
        int firstClientSocket = accept(this->serverSocket_, (struct sockaddr *)&firstClientAddress,
                                  &firstClientAddressLen);
        cout << "first player connected" << endl;
        if (firstClientSocket == -1) {
            throw "Error on accept player1";
        }

        cout << "Waiting for second player to connect..." << endl;
        // Accept a new client connection
        int secondClientSocket = accept(this->serverSocket_, (struct sockaddr *)&secondClientAddress,
                                       &secondClientAddressLen);
        cout << "second player connected" << endl;
        if (secondClientSocket == -1) {
            // Close communication with the client
            close(firstClientSocket);
            throw "Error on accept player2";
        }

        // send players numbers for the clients
        int playerNumber = 1;
        int stat;
        stat = write(firstClientSocket, &playerNumber, sizeof(playerNumber));
        playerNumber = 2;
        stat = write(secondClientSocket, &playerNumber, sizeof(playerNumber));

        // set counters
        int turnCounter = 0;
        bool end = false;

        // game loop
        while (!end) {
            if (turnCounter % 2 == 0) {
                // handle move of the first player
                end = handleMove(firstClientSocket, secondClientSocket);

            } else {
                // handle move of the second player
                end = handleMove(secondClientSocket, firstClientSocket);

            }
            turnCounter++;
        }

        // close sockets
        close(firstClientSocket);
        close(secondClientSocket);
    }
}

bool Server::handleMove(int fromSocket, int toSocket) {
    char moveBuff[BUFFER_SIZE];

    cout << "wait for receiving move from socket: " << fromSocket << endl;

    // read from first client
    int stat = read(fromSocket, &moveBuff, sizeof(moveBuff));
    if (stat == -1) {
        cout << "Error reading moveBuff" << endl;
        return true;
    }
    if (stat == 0) {
        cout << "Client disconnected" << endl;
        return true;
    }
    if (strcmp(moveBuff, "END") == 0) {
        cout << "End of game" << endl;
        return true;
    }
    cout << "Got move: " << moveBuff << endl;

    // write to the second client
    stat = write(toSocket, moveBuff, sizeof(moveBuff));
    if (stat == -1) {
        cout << "Error writing moveBuff" << endl;
        return true;
    }
    if (stat == 0) {
        cout << "Client disconnected" << endl;
        return true;
    }
    cout << "Sent Move:" << moveBuff << endl;
    return false;
}


void Server::stop() {
    close(this->serverSocket_);
}
