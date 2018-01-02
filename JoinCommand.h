//
// Created by dvir on 22/12/17.
//

#ifndef REVERSISERVER_JOINCOMMAND_H
#define REVERSISERVER_JOINCOMMAND_H


#include "Command.h"
#include "Server.h"
#include "GameRoomsController.h"
#include <iostream>
#include <sstream>

using namespace std;

class JoinCommand: public Command {
public:
    /**
     * constructor
     * @param server - server
     */
    JoinCommand(Server *server);
    /**
     * execute the command
     * @param args - list of args of the command
     */
    virtual void execute(vector<string> args);
    /**
     * destructor
     */
    virtual ~JoinCommand();

private:
    Server *server_;
};


#endif //REVERSISERVER_JOINCOMMAND_H
