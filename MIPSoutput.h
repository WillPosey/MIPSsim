/************************************************
 * 		MIPSoutput.h
 *
 *      Author: William Posey
 *      Course: CDA 5155
 *      Project 1: MIPS Disassembler
 *
 *      Header file for the MIPSoutput class
 ************************************************/

#ifndef MIPS_OUTPUT_H
#define MIPS_OUTPUT_H

#include "MIPSdefs.h"
#include "MIPS_Buffer.h"
#include "WorkThread.h"

#include <string>
#include <fstream>
#include <iostream>

using namespace std;

// used for WorkThread thread function
void* writeOutput(void*);

class MIPSoutput {
public:
    // allow thread function access to private members
    friend void* writeOutput(void*);

    /*
     * Constructor assigns MIPS_Buffer<OutputData> reference,
     * sets the output filename,
     * and creates a new WorkThread with the writeOutput function pointer
     */
	MIPSoutput(MIPS_Buffer<OutputData> &output, string outputFilename) :outputInfo(output)
    {
        thread = new WorkThread(writeOutput,this);
        filename = outputFilename;
    }

    // Destructor
	virtual ~MIPSoutput(){}

    // Activates WorkThread to run the writeOutput function
    // and waits for the output to complete
	void WriteResults()
	{
        thread->Activate();
        thread->JoinThread();
    }

private:
    // filename to write output to
	string	filename;

	// Buffer written to from InstructionDecode stage
	MIPS_Buffer<OutputData> &outputInfo;

	// WorkThread used to carry out the writing of the disassembled results
	WorkThread* thread;
};

#endif /* MIPS_OUTPUT_H */
