/********************************************************************
 * 		WorkThread.h
 *
 *      Author: William Posey
 *      Course: CDA 5155
 *      Project 1: MIPS Disassembler
 *
 *      The WorkThread class is used to encapsulate a POSIX thread,
 *      which is used to run a simple work function for an object
 ********************************************************************/

#ifndef WORK_THREAD_H
#define WORK_THREAD_H

#include <pthread.h>

class WorkThread {
public:
    /* Constructor
     *
     * The constructor accepts a function pointer that is the work to be done in the thread
     * as well as a pointer to the object using the work function, to allow access to members and functions
     */
	WorkThread(void* (*f)(void*), void* obj)
	{
        this->RunFunction = f;
        object = obj;
    }

    /* Destructor */
	virtual ~WorkThread(){}

    /* Activates the thread and runs the supplied RunFunction */
	void Activate()
	{
        if(pthread_create(&threadID, NULL, RunFunction, object))
            isActive = false;
        else
            isActive = true;
    }

    /* Joins the thread to wait forthe completion of the RunFunction */
	void JoinThread()
	{
        if(isActive)
            pthread_join(threadID, NULL);
    }

private:
    bool isActive;
    void* (*RunFunction)(void*);
    void* object;
    pthread_t threadID;
};

#endif /* WORK_THREAD_H */

