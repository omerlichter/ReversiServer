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
     * handle read and write the move
     * @param fromSocket - read from client socket
     * @param toSocket - write to client socket
     * @return true if game end or player disconnect, and false if else.
     */
    bool handleMove(int fromSocket, int toSocket) ;
};


#endif //REVERSISERVER_SERVER_H
