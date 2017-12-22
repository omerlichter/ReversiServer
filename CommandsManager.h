//
// Created by omer on 12/21/17.
//

#ifndef REVERSISERVER_COMMANDSMANAGER_H
#define REVERSISERVER_COMMANDSMANAGER_H

#include <map>
#include "Command.h"

class CommandsManager {
public:
    CommandsManager() ;
    ~CommandsManager() ;
    void executeCommand(string command, vector<string> args) ;
private:
    map<string, Command *> commandsMap_;
};


#endif //REVERSISERVER_COMMANDSMANAGER_H
