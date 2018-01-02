//
// Created by omer on 12/29/17.
//

#ifndef REVERSISERVER_CLOSESERVERCOMMAND_H
#define REVERSISERVER_CLOSESERVERCOMMAND_H

#include "Command.h"
#include "Server.h"
#include "GameRoomsController.h"
#include <sstream>

class CloseServerCommand : public Command {
public:
    /**
     * constructor
     * @param server - server
     */
    CloseServerCommand(Server *server);
    /**
     * destructor
     */
    virtual ~CloseServerCommand();
    /**
     * execute the command
     * @param args - list of args of the command
     */
    virtual void execute(vector<string> args);
private:
    Server *server_;
};


#endif //REVERSISERVER_CLOSESERVERCOMMAND_H
