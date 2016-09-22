/***************************************************
 * 		InstructionFetch.h
 *
 *      Author: William Posey
 *      Course: CDA 5155
 *      Project 1: MIPS Disassembler
 *
 *      Header file for the InstructionFetch class
 ***************************************************/

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
    // allow thread function access to private members
    friend void* readBinaries(void*);

    // Constructor assigns the two MIPS_Buffer references and creates new WorkThread with readBrinaries function pointer
	InstructionFetch( MIPS_Buffer<BinaryInfo> &bin, MIPS_Buffer<MemoryLocation> &mem ) : binaries(bin), memoryLocations(mem)
    {thread = new WorkThread(readBinaries, (void*) this);}

    // Destructor
	virtual ~InstructionFetch(){}

    // run readBinaries through WorkThread
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
