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
#define THREADS_NUM 5

Server::Server(int port): port_(port), serverSocket_(0), threadPool_(ThreadPool(THREADS_NUM)) {
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
    pthread_create(&this->acceptThread_, NULL, this->accpetsLoop, (void *)this);
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
        Task *task = new Task(handleClient, (void *)hcStruct);
        serverP->threadPool_.addTask(task);
    }
}

void Server::addTask(Task *task) {
    this->threadPool_.addTask(task);
}

void Server::writeToClient(int clientSocket, const string &message) {
    const char *messageBuff = message.c_str();
    char buff[BUFFER_SIZE];
    for (int i = 0; i < BUFFER_SIZE; i++) {
        if (i < message.size()) {
            buff[i] = messageBuff[i];
        } else {
            buff[i] = '\0';
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
    cout << "end handle client" << endl;
}

void Server::stop() {

    cout << "close the server" << endl;
    pthread_cancel(this->acceptThread_);
    this->threadPool_.terminate();
    close(this->serverSocket_);
}
