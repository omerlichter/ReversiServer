//
// Created by omer on 12/21/17.
//

#ifndef REVERSISERVER_COMMANDSMANAGER_H
#define REVERSISERVER_COMMANDSMANAGER_H

#include <map>
#include "Command.h"
#include "Server.h"
#include "CloseCommand.h"
#include "CloseServerCommand.h"
#include "JoinCommand.h"
#include "ListOfGamesCommand.h"
#include "StartCommand.h"

class CommandsManager {
public:
    /**
     * constructor
     * @param server - server
     */
    CommandsManager(Server *server) ;
    /**
     * destructor
     */
    ~CommandsManager() ;
    /**
     * exevute the command
     * @param command - name of the command
     * @param args - list of args of the command
     */
    void executeCommand(string command, vector<string> args) ;
private:
    map<string, Command *> commandsMap_;
};


#endif //REVERSISERVER_COMMANDSMANAGER_H
