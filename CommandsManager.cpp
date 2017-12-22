//
// Created by omer on 12/21/17.
//

#include "CommandsManager.h"
#include "CloseCommand.h"
#include "JoinCommand.h"
#include "ListOfGamesCommand.h"
#include "PlayCommand.h"
#include "StartCommand.h"

CommandsManager::CommandsManager() {
    // here we crate all the options of command
    this->commandsMap_["close"] = new CloseCommand();
    this->commandsMap_["join"] = new JoinCommand();
    this->commandsMap_["list_games"] = new ListOfGamesCommand();
    this->commandsMap_["play"] = new PlayCommand();
    this->commandsMap_["start"] = new StartCommand();

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