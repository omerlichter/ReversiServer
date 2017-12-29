#include "Server.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include <pthread.h>
#include "CommandsManager.h"

using namespace std;

#define MAX_CONNECTED_CLIENTS 2
#define BUFFER_SIZE 255

pthread_mutex_t threads_mutex;

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

    // create accept loop thread
    pthread_t acceptLoopThread;
    pthread_create(&acceptLoopThread, NULL, this->accpetsLoop, (void *)this);

    // waiting for exit command
    string command;
    do {
        cin >> command;
    } while (command != "exit");

    cout << "kill all threads:" << endl;
    // close all threads
    pthread_mutex_lock(&threads_mutex);
    for (vector<pthread_t *>::iterator it = threads.begin();
         it != threads.end(); it++) {
        cout << "kill thread" << endl;
        pthread_cancel(**it);
    }
    pthread_mutex_unlock(&threads_mutex);

    // close all game rooms
    vector<string> args;
    args.push_back("");
    CommandsManager commandsManager(this);
    commandsManager.executeCommand("close_server", args);
}

void* Server::accpetsLoop(void *server) {

    cout << "start the accept loop thraed" << endl;

    Server *serverP = (Server*) server;

    // Define the client socket's structures
    struct sockaddr_in clientAddress;
    socklen_t clientAddressLen = sizeof((struct sockaddr *)&clientAddress);

    while (true) {
        cout << "Waiting for client connections..." << endl;
        // Accept a new client connection
        long clientSocket = accept(serverP->serverSocket_,
                                   (struct sockaddr *)&clientAddress, &clientAddressLen);
        cout << "Client connected" << endl;
        if (clientSocket == -1)
            throw "Error on accept";
        HCStruct *hcStruct = new HCStruct;
        hcStruct->clientSocket = clientSocket;
        hcStruct->server = serverP;
        pthread_t *thread = new pthread_t;
        pthread_mutex_lock(&threads_mutex);
        serverP->threads.push_back(thread);
        pthread_mutex_unlock(&threads_mutex);
        pthread_create(thread, NULL, handleClient, (void *)hcStruct);
    }
}

void Server::writeToClient(int clientSocket, const string &message) {
    const char *messageBuff = message.c_str();
    char buff[BUFFER_SIZE];
    for (int i = 0; i < BUFFER_SIZE; i++) {
        if (i < message.size()) {
            buff[i] = messageBuff[i];
        } else {
            buff[i] = '\0';
            break;
        }
    }
    int stat = write(clientSocket, buff, sizeof(buff));
    if (stat == -1) {
        throw "Error on reading buffer";
    }
    if (stat == 0) {
        throw "client disconnected";
    }
}

string Server::readFromClient(int clientSocket) {
    char buff[BUFFER_SIZE];
    int stat = read(clientSocket, buff, sizeof(buff));
    if (stat == -1) {
        throw "Error on reading buffer";
    }
    if (stat == 0) {
        throw "client disconnected";
    }
    string message(buff);
    return message;
}

void Server::closeClient(int clientSocket) {
    close(clientSocket);
}

void *Server::handleClient(void *hcStruct) {
    HCStruct *hcStruct1 = (HCStruct*)hcStruct;
    Server *server = hcStruct1->server;
    int clientSocket = hcStruct1->clientSocket;
    delete(hcStruct1);
    cout << "handle client in thread" << endl;

    string buffString;
    try {
        buffString = server->readFromClient(clientSocket);
    } catch (const char *message) {
        cout << message << endl;
        pthread_exit(NULL);
    }
    // split the string to command and args
    int pos = buffString.find(" ");
    string commandString = buffString.substr(0, pos);
    string argsString = buffString.substr(pos + 1);

    // cast the client socket to int
    stringstream stringstream1;
    stringstream1 << clientSocket;
    string clientSocketString = stringstream1.str();

    // send to the command
    vector<string> args;
    args.push_back(clientSocketString);
    args.push_back(argsString);
    CommandsManager commandsManager(server);
    commandsManager.executeCommand(commandString, args);

    // exit thread
    cout << "exit thread" << endl;
    pthread_exit(NULL);
}

void Server::stop() {
    close(this->serverSocket_);
}
