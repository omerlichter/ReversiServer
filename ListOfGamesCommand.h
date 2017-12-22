//
// Created by dvir on 22/12/17.
//

#ifndef REVERSISERVER_LISTOFGAMESCOMMAND_H
#define REVERSISERVER_LISTOFGAMESCOMMAND_H


#include "Command.h"

class ListOfGamesCommand: public Command {
    virtual void execute(vector<string> args);
    virtual ~ListOfGamesCommand();
};


#endif //REVERSISERVER_LISTOFGAMESCOMMAND_H
