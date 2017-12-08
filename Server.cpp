#include "Server.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <stdio.h>

using namespace std;

#define MAX_CONNECTED_CLIENTS 2

Server::Server(int port): port_(port), serverSocket_(0) {
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
    struct sockaddr_in clientAddress;
    socklen_t clientAddressLen = sizeof((struct sockaddr *)&clientAddress);

    //
    while (true) {
        cout << "Waiting for first player to connect..." << endl;
        // Accept a new client connection
        int firstClientSocket = accept(this->serverSocket_, (struct sockaddr *)&clientAddress,
                                  &clientAddressLen);
        cout << "first player connected" << endl;
        if (firstClientSocket == -1) {
            throw "Error on accept player1";
        }

        cout << "Waiting for second player to connect..." << endl;
        // Accept a new client connection
        int secondClientSocket = accept(this->serverSocket_, (struct sockaddr *)&clientAddress,
                                       &clientAddressLen);
        cout << "second player connected" << endl;
        if (secondClientSocket == -1) {
            // Close communication with the client
            close(firstClientSocket);
            throw "Error on accept player2";
        }

        int playerNumber = 1;
        int stat;
        stat = write(firstClientSocket, &playerNumber, sizeof(playerNumber));
        playerNumber = 2;
        stat = write(secondClientSocket, &playerNumber, sizeof(playerNumber));

        int turnCounter = 0;
        bool end = false;

        while (!end) {
            if (turnCounter % 2 == 0) {
                end = handleMove(firstClientSocket, secondClientSocket);

            } else {
                end = handleMove(secondClientSocket, firstClientSocket);

            }
            turnCounter++;
        }

        close(firstClientSocket);
        close(secondClientSocket);
    }
}

bool Server::handleMove(int fromSocket, int toSocket) {
    char moveBuff[10];

    cout << "wait for receiving move from socket: " << fromSocket << endl;

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
