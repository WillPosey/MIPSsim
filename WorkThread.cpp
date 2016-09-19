/************************************************
 * 		WorkThread.cpp
 *
 *      Author: William Posey
 *      Course: CDA 5155
 *      Project 1: MIPS Disassembler
 ************************************************/
#include "WorkThread.h"

using namespace std;

void WorkThread::Activate()
{
    if(pthread_create(&threadID, NULL, RunFunction, object))
        isActive = false;
    else
        isActive = true;
}
/*
static void* RunFunction(void* obj)
{
    reinterpret_cast<WorkThread*>(obj)->Run();
    return NULL;
}*/


