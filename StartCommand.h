//
// Created by dvir on 22/12/17.
//

#ifndef REVERSISERVER_STARTCOMMAND_H
#define REVERSISERVER_STARTCOMMAND_H

#include <sstream>
#include "Server.h"
#include "Command.h"

class StartCommand: public Command {
public:
    StartCommand(Server *server);
    virtual void execute(vector<string> args);
    virtual ~StartCommand();

private:
    Server *server_;
};


#endif //REVERSISERVER_STARTCOMMAND_H
