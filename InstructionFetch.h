/************************************************
 * 		InstructionFetch.h
 *
 *      Author: William Posey
 *      Course: CDA 5155
 *      Project 1: MIPS Disassembler
 ************************************************/

#ifndef INSTRUCTION_FETCH_H
#define INSTRUCTION_FETCH_H

#include "MIPSdefs.h"
#include "MIPS_Buffer.h"
#include "WorkThread.h"

using namespace std;

// used for WorkThread thread function
void* readBinaries(void*);

class InstructionFetch {
public:
    friend void* readBinaries(void*);
	InstructionFetch(   MIPS_Buffer<BinaryInfo> &bin,
                        MIPS_Buffer<MemoryLocation> &mem
                    ) : binaries(bin), memoryLocations(mem)
                    {thread = new WorkThread(readBinaries, (void*) this);}
	virtual ~InstructionFetch(){}

	void GetInstructions(){thread->Activate();}

private:
    // Buffers used to read binary info from MIPSinput
    // and write memory location info for InstructionDecode
    MIPS_Buffer<BinaryInfo> &binaries;
    MIPS_Buffer<MemoryLocation> &memoryLocations;

	// WorkThread used to carry out the retrieval of the binary input
	WorkThread* thread;
};

#endif /* INSTRUCTION_FETCH_H */
