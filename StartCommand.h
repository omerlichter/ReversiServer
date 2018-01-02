//
// Created by dvir on 22/12/17.
//

#ifndef REVERSISERVER_STARTCOMMAND_H
#define REVERSISERVER_STARTCOMMAND_H

#include <sstream>
#include "Server.h"
#include "GameRoomsController.h"
#include "Command.h"

class StartCommand: public Command {
public:
    /**
     * constructor
     * @param server - server
     */
    StartCommand(Server *server);
    /**
     * execute the command
     * @param args - list of args of the command
     */
    virtual void execute(vector<string> args);
    /**
     * destructor
     */
    virtual ~StartCommand();

private:
    Server *server_;
};


#endif //REVERSISERVER_STARTCOMMAND_H
