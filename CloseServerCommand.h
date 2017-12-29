//
// Created by omer on 12/29/17.
//

#ifndef REVERSISERVER_CLOSESERVERCOMMAND_H
#define REVERSISERVER_CLOSESERVERCOMMAND_H

#include "Command.h"
#include "Server.h"
#include <sstream>

class CloseServerCommand : public Command {
public:
    CloseServerCommand(Server *server);
    virtual ~CloseServerCommand();
    virtual void execute(vector<string> args);
private:
    Server *server_;
};


#endif //REVERSISERVER_CLOSESERVERCOMMAND_H
