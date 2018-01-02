//
// Created by omer on 12/21/17.
//

#include "CommandsManager.h"

CommandsManager::CommandsManager(Server *server) {
    // here we crate all the options of command
    this->commandsMap_["close"] = new CloseCommand(server);
    this->commandsMap_["close_server"] = new CloseServerCommand(server);
    this->commandsMap_["join"] = new JoinCommand(server);
    this->commandsMap_["list_games"] = new ListOfGamesCommand(server);
    this->commandsMap_["start"] = new StartCommand(server);

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