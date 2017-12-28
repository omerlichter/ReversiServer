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

    void writeToClient(int clientSocket, const string &message);

    string readFromClient(int clientSocket);

    void closeClient(int clientSocket);

private:
    int port_;
    int serverSocket_;

    static void *handleClient(void *hcStruct) ;
};

typedef struct struct1 {
    int clientSocket;
    Server * server;
} HCStruct;


#endif //REVERSISERVER_SERVER_H
