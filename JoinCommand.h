//
// Created by dvir on 22/12/17.
//

#ifndef REVERSISERVER_JOINCOMMAND_H
#define REVERSISERVER_JOINCOMMAND_H


#include "Command.h"

class JoinCommand: public Command {
    virtual void JoinCommand::execute(vector<string> args);
    virtual JoinCommand::~Command();
};


#endif //REVERSISERVER_JOINCOMMAND_H
