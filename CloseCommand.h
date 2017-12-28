//
// Created by dvir on 22/12/17.
//

#ifndef REVERSISERVER_CLOSECOMMAND_H
#define REVERSISERVER_CLOSECOMMAND_H


#include "Command.h"
#include "Server.h"
#include <sstream>

class CloseCommand: public Command {
public:
    CloseCommand(Server *server);
    virtual ~CloseCommand();
    virtual void execute(vector<string> args);

private:
    Server *server_;
};


#endif //REVERSISERVER_CLOSECOMMAND_H
