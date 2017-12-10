#include <iostream>
#include "Server.h"
#include <stdlib.h>
#include <fstream>

using namespace std;

int main() {

    // get port from file
    int port;
    ifstream inFile;
    inFile.open("setting_server.txt");
    inFile >> port;

    // set server
    Server server(port);
    try {
        // start the server
        server.start();
    } catch (const char *msg) {
        cout << "Cannot start server. Reason: " << msg << endl;
        server.stop();
        exit(-1);
    }
}