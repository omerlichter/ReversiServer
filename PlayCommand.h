//
// Created by dvir on 22/12/17.
//

#ifndef REVERSISERVER_PLAYCOMMAND_H
#define REVERSISERVER_PLAYCOMMAND_H


#include "Command.h"

class PlayCommand: public Command {
    virtual void PlayCommand::execute(vector<string> args);
    virtual PlayCommand::~Command();
};


#endif //REVERSISERVER_PLAYCOMMAND_H
