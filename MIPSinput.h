/************************************************
 * 		MIPSinput.h
 *
 *      Author: William Posey
 *      Course: CDA 5155
 *      Project 1: MIPS Disassembler
 ************************************************/

#ifndef MIPSINPUT_H_
#define MIPSINPUT_H_

#include <string>
#include <stdint.h>
#include <istream>

#define INSTRUCTION_SIZE_BYTES 4

using namespace std;

class MIPSinput {
public:
	MIPSinput(){}
	virtual ~MIPSinput();

	// Methods to parse command line and file input
	bool	ParseInput(int optionCount, char** options);
	void	ParseBinaryFile();

	// Prints error from ParseInput()
	void	PrintError();

	// Methods to retrieve command line options
	string 	GetInputFilename()	{return inputFileName;}
	string 	GetOutputFilename()	{return outputFileName;}
	string 	GetOperation()		{return operation;}
	bool	IsTraceOptPresent()	{return traceOptionPresent;}
	int 	GetTraceStart()		{return traceOptionPresent ? traceStart : -1;}
	int 	GetTraceEnd()		{return traceOptionPresent ? traceEnd : -1;}

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

	// binary input file members
	int		numInstructions;
	uint32_t *instructions;

	// string to hold error message
	bool	errorOccured;
	string	errorMessage;
};

#endif /* MIPSINPUT_H_ */
