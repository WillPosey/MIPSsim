/******************************************************************************************
 * 		MIPS_Buffer.h
 *
 *      Author: William Posey
 *      Course: CDA 5155
 *      Project 1: MIPS Disassembler
 *
 *      The MIPS_Buffer template class encapsulates a queue of the template type,
 *      and allows synchronization between a buffer writer and reader through a semaphore
 ******************************************************************************************/

#ifndef MIPS_BUFFER_H
#define MIPS_BUFFER_H

#include "MIPSdefs.h"

#include <queue>
#include <semaphore.h>

using namespace std;

template <class bufferType>
class MIPS_Buffer {
public:
    /*  Constructor
     *  The constructor initializes the semaphore and sets the writeComplete false
     */
    MIPS_Buffer()
    {
        sem_init(&lock, 0, 1);
        writeComplete = false;
    }

    /* Destructor, destroys semahpore*/
    ~MIPS_Buffer(){sem_destroy(&lock);}

    // Reads the front of the queue
    bool ReadBuffer(bufferType& data)
    {
        static struct timespec delay = {0,500000000}; // half a second

        sem_wait(&lock);

        while(buffer.empty())
        {
            if(writeComplete)
                return false;
            sem_post(&lock);
            nanosleep(&delay, NULL);
            sem_wait(&lock);
        }

        data = buffer.front();
        buffer.pop();

        sem_post(&lock);
        return true;
    }

    // Writes to the back of the queue
    void WriteBuffer(bufferType data)
    {
        sem_wait(&lock);
        buffer.push(data);
        sem_post(&lock);
    }

    // Sets the writer complete flag so reader stops reading from queue
    void WriterComplete()
    {
        sem_wait(&lock);
        writeComplete = true;
        sem_post(&lock);
    }

private:
    queue<bufferType> buffer;
    sem_t lock;
    bool writeComplete;
};

#endif /* MIPS_BUFFER_H */
