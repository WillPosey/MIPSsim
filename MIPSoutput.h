/************************************************
 * 		MIPSoutput.h
 *
 *      Author: William Posey
 *      Course: CDA 5155
 *      Project 1: MIPS Disassembler
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

	MIPSoutput(MIPS_Buffer<OutputData> &output, string outputFilename)
              :outputInfo(output)
              {
                thread = new WorkThread(writeOutput,this);
                filename = outputFilename;
              }
	virtual ~MIPSoutput(){}

	void WriteResults(){ thread->Activate(); }//thread->JoinThread(); }
	WorkThread* thread;

private:
	string	filename;
	MIPS_Buffer<OutputData> &outputInfo;

	// WorkThread used to carry out the writing of the disassembled results
	//WorkThread* thread;
};

#endif /* MIPS_OUTPUT_H */
