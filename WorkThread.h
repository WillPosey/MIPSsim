/************************************************
 * 		WorkThread.h
 *
 *      Author: William Posey
 *      Course: CDA 5155
 *      Project 1: MIPS Disassembler
 ************************************************/

#ifndef WORK_THREAD_H
#define WORK_THREAD_H

#include <pthread.h>

using namespace std;

class WorkThread {
public:
	WorkThread(void* (*f)(void*), void* obj){this->RunFunction = f; object = obj;}
	virtual ~WorkThread(){}
	//virtual void Run(){}

    //void SetWorkFunction(void (*f)(void*)){workFunction = f;}
	void Activate();
	void JoinThread(){if(isActive) pthread_join(threadID, NULL);}

private:
    bool isActive;
    void* (*RunFunction)(void*);
    void* object;
    pthread_t threadID;
};

#endif /* WORK_THREAD_H */

