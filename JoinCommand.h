//
// Created by dvir on 22/12/17.
//

#ifndef REVERSISERVER_JOINCOMMAND_H
#define REVERSISERVER_JOINCOMMAND_H


#include "Command.h"
#include "Server.h"
#include <iostream>
#include <sstream>

using namespace std;

class JoinCommand: public Command {
public:
    JoinCommand(Server *server);
    virtual void execute(vector<string> args);
    virtual ~JoinCommand();

private:
    Server *server_;
};


#endif //REVERSISERVER_JOINCOMMAND_H
