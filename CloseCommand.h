//
// Created by dvir on 22/12/17.
//

#ifndef REVERSISERVER_CLOSECOMMAND_H
#define REVERSISERVER_CLOSECOMMAND_H


#include "Command.h"
#include "Server.h"
#include "GameRoomsController.h"
#include <sstream>

class CloseCommand: public Command {
public:
    /**
     * constructor
     * @param server - server
     */
    CloseCommand(Server *server);
    /**
     * destructor
     */
    virtual ~CloseCommand();
    /**
     * execute the command
     * @param args - list of the args of the command
     */
    virtual void execute(vector<string> args);

private:
    Server *server_;
};


#endif //REVERSISERVER_CLOSECOMMAND_H
