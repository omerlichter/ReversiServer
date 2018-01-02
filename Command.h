//
// Created by omer on 12/21/17.
//

#ifndef REVERSISERVER_COMMAND_H
#define REVERSISERVER_COMMAND_H

#include <vector>
#include <string>

using namespace std;

class Command {
public:
    /**
     * execute the command
     * @param args - list of args of the command
     */
    virtual void execute(vector<string> args) = 0 ;
    /**
     * destructor
     */
    virtual ~Command() {}
};


#endif //REVERSISERVER_COMMAND_H
