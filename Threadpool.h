//
// Created by omer on 1/12/18.
//

#ifndef REVERSISERVER_THREADPOOL_H
#define REVERSISERVER_THREADPOOL_H


#include "Task.h"
#include <queue>
#include <pthread.h>
using namespace std;
class ThreadPool {
public:
    /**
     * constructor
     * @param threadsNum number of threads in the pool
     */
    ThreadPool(int threadsNum);
    /**
     * add task to the queue
     * @param task task to add
     */
    void addTask(Task *task);
    /**
     * terminate the thread pool
     */
    void terminate();
    /**
     * destructor
     */
    virtual ~ThreadPool();
private:
    queue<Task *> tasksQueue;
    pthread_t* threads;
    void executeTasks();
    bool stopped;
    pthread_mutex_t lock;
    static void *execute(void *arg);
};


#endif //REVERSISERVER_THREADPOOL_H
