//
// Created by omer on 12/1/17.
//

#ifndef REVERSISERVER_SERVER_H
#define REVERSISERVER_SERVER_H


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
    /**
     * handle move to the client
     * @param clientSocket - client socket
     */
    void handleMove(int fromSocket, int toSocket) ;
};


#endif //REVERSISERVER_SERVER_H
