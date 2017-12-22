//
// Created by dvir on 22/12/17.
//

#ifndef REVERSISERVER_CLOSECOMMAND_H
#define REVERSISERVER_CLOSECOMMAND_H


#include "Command.h"

class CloseCommand: public Command {
    virtual ~CloseCommand();
    virtual void execute(vector<string> args);
};


#endif //REVERSISERVER_CLOSECOMMAND_H
