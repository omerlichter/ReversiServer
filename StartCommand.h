//
// Created by dvir on 22/12/17.
//

#ifndef REVERSISERVER_STARTCOMMAND_H
#define REVERSISERVER_STARTCOMMAND_H


#include "Command.h"

class StartCommand: public Command {
    virtual void StartCommand::execute(vector<string> args);
    virtual StartCommand::~Command();
};


#endif //REVERSISERVER_STARTCOMMAND_H
