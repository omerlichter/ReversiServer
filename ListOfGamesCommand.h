//
// Created by dvir on 22/12/17.
//

#ifndef REVERSISERVER_LISTOFGAMESCOMMAND_H
#define REVERSISERVER_LISTOFGAMESCOMMAND_H


#include <sstream>
#include "Server.h"
#include "Command.h"

class ListOfGamesCommand: public Command {
public:
    ListOfGamesCommand(Server *server);
    virtual void execute(vector<string> args);
    virtual ~ListOfGamesCommand();

private:
    Server *server_;
};


#endif //REVERSISERVER_LISTOFGAMESCOMMAND_H
