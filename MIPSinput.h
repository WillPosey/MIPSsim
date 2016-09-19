/************************************************
 * 		MIPSinput.h
 *
 *      Author: William Posey
 *      Course: CDA 5155
 *      Project 1: MIPS Disassembler
 ************************************************/

#ifndef MIPSINPUT_H_
#define MIPSINPUT_H_

#include "MIPSdefs.h"
#include "MIPS_Buffer.h"
#include "WorkThread.h"

#include <string>
#include <stdint.h>
#include <istream>
#include <vector>
#include <iostream>

using namespace std;

// used for WorkThread thread function
void* readInput(void*);

class MIPSinput {
public:
    // allow thread function access to private members
    friend void* readInput(void*);

	MIPSinput(MIPS_Buffer<BinaryInfo> &input):binaries(input){thread = new WorkThread(readInput,this);}
	virtual ~MIPSinput(){}

	// Methods to parse command line and file input
	bool	ParseInput(int optionCount, char** options);
	void	ParseBinaryFile(){thread->Activate();}

	// Prints error from ParseInput()
	void	PrintError();

	// Methods to retrieve command line options
	string 	GetInputFilename()	{return inputFileName;}
	string 	GetOutputFilename()	{return outputFileName;}
	string 	GetOperation()		{return operation;}
	bool	IsTraceOptPresent()	{return traceOptionPresent;}
	int 	GetTraceStart()		{return traceOptionPresent ? traceStart : -1;}
	int 	GetTraceEnd()		{return traceOptionPresent ? traceEnd : -1;}

	// Methods to retrieve instruction data from input file
	int     GetNumberMemoryLocations()  {return numLocations;}
	//vector<BinaryInfo>  GetBinaryInput()            {return binaryInput;}

private:

	// command line option indexes in char** argv
	enum
	{
		IN_FILENAME_INDEX	= 1,
		OUT_FILENAME_INDEX	= 2,
		OPERATION_INDEX		= 3,
		TRACE_OPT_INDEX		= 4
	};

	// command line input members
	string	inputFileName;
	string	outputFileName;
	string	operation;
	string	traceOption;
	bool	traceOptionPresent;
	int		traceStart;
	int		traceEnd;

	// binary input file members and methods
	vector<BinaryInfo>       binaryInput;
	MIPS_Buffer<BinaryInfo>  &binaries;
	int		numLocations;
	void    SwapBitOrder(uint8_t* byte);

	// string to hold error message
	bool	errorOccured;
	string	errorMessage;

	// WorkThread used to carry out the retrieval of the binary input
	WorkThread* thread;
};

#endif /* MIPSINPUT_H_ */
