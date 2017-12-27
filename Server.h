#ifndef REVERSISERVER_SERVER_H
#define REVERSISERVER_SERVER_H

#include "GameRoom.h"
#include <vector>

class Server {
public:
    /**
     * constructor
     * @param port - port of the server
     */
    Server(int port) ;
    /**
     * start server
     */
    void start() ;
    /**
     * stop server
     */
    void stop() ;

    void writeToClient(int clientSocket, const string &message);

    string readFromClient(int clientSocket);

    void closeClient(int clientSocket);

private:
    int port_;
    int serverSocket_;

    /**
     * handle read and write the move
     * @param fromSocket - read from client socket
     * @param toSocket - write to client socket
     * @return true if game end or player disconnect, and false if else.
     */
    bool handleMove(int fromSocket, int toSocket) ;

    friend void *handleClient(void *clientSocket) ;
};

typedef struct struct1 {
    int clientSocket;
    Server * server;
} HCStruct;


void *handleClient(void *HCStruct) ;


#endif //REVERSISERVER_SERVER_H
