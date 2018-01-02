//
// Created by dvir on 22/12/17.
//

#ifndef REVERSISERVER_LISTOFGAMESCOMMAND_H
#define REVERSISERVER_LISTOFGAMESCOMMAND_H


#include <sstream>
#include "Server.h"
#include "Command.h"
#include "GameRoomsController.h"

class ListOfGamesCommand: public Command {
public:
    /**
     * constructor
     * @param server - server
     */
    ListOfGamesCommand(Server *server);
    /**
     * execute the command
     * @param args - list of args of the command
     */
    virtual void execute(vector<string> args);
    /**
     * destructor
     */
    virtual ~ListOfGamesCommand();

private:
    Server *server_;
};


#endif //REVERSISERVER_LISTOFGAMESCOMMAND_H
