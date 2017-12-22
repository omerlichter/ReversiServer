#ifndef REVERSISERVER_SERVER_H
#define REVERSISERVER_SERVER_H

#include "CommandsManager.h"
#include "GameRoom.h"

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

private:
    int port_;
    int serverSocket_;
    CommandsManager commandsManager_;
    vector<GameRoom *> *gameRooms_;

    /**
     * handle read and write the move
     * @param fromSocket - read from client socket
     * @param toSocket - write to client socket
     * @return true if game end or player disconnect, and false if else.
     */
    bool handleMove(int fromSocket, int toSocket) ;

    friend void *handleClient(void *clientSocket) ;
};

void *handleClient(void *clientSocket) ;


#endif //REVERSISERVER_SERVER_H
