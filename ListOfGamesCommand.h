//
// Created by dvir on 22/12/17.
//

#ifndef REVERSISERVER_LISTOFGAMESCOMMAND_H
#define REVERSISERVER_LISTOFGAMESCOMMAND_H


#include "Command.h"

class ListOfGamesCommand: public Command {
    virtual void ListOfGamesCommand::execute(vector<string> args);
    virtual ListOfGamesCommand::~Command();
};


#endif //REVERSISERVER_LISTOFGAMESCOMMAND_H
