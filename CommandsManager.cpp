//
// Created by omer on 12/21/17.
//

#include "CommandsManager.h"

CommandsManager::CommandsManager() {
    // here we crate all the options of command
}

CommandsManager::~CommandsManager() {
    map<string, Command *>::iterator it;
    for (it = commandsMap_.begin(); it != commandsMap_.end(); it++) {
        delete it->second;
    }
}

void CommandsManager::executeCommand(string command, vector<string> args) {
    Command *commandObj = this->commandsMap_[command];
    commandObj->execute(args);
}