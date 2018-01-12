//
// Created by omer on 1/12/18.
//

#ifndef REVERSISERVER_TASK_H
#define REVERSISERVER_TASK_H


class Task {
public:
    /**
     * constructor
     * @param func function to run
     * @param arg argument to the function
     */
    Task(void * (*func)(void *arg), void* arg) : func(func), arg(arg) {}
    /**
     * execute the function with the args
     */
    void execute() {
        func(arg);
    }
    /**
     * destructor
     */
    virtual ~Task() {}
private:
    void * (*func)(void *arg);
    void *arg;
};


#endif //REVERSISERVER_TASK_H
