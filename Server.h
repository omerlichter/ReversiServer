#ifndef REVERSISERVER_SERVER_H
#define REVERSISERVER_SERVER_H

#include <iostream>
#include <vector>

using namespace std;

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

    /**
     * write string to client
     * @param clientSocket - socket id of the client
     * @param message - string message
     */
    void writeToClient(int clientSocket, const string &message);

    /**
     * read string from the clinet
     * @param clientSocket - socket id of the client
     * @return the message
     */
    string readFromClient(int clientSocket);

    /**
     * close client communication
     * @param clientSocket - socket id of the client
     */
    void closeClient(int clientSocket);

private:
    int port_;
    int serverSocket_;
    pthread_t acceptThread_;

    /**
     * static function for run the accept loop in thraed
     * @param server - server
     * @return nothing
     */
    static void *accpetsLoop(void *server);

    /**
     * static function for handle client in thread
     * @param hcStruct - struct that contain client socket and server
     * @return nothing
     */
    static void *handleClient(void *hcStruct) ;
};

// struct
typedef struct struct1 {
    int clientSocket;
    Server * server;
} HCStruct;


#endif //REVERSISERVER_SERVER_H
