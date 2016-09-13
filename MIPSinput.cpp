/**************************************************************
 * 		MIPSinput.cpp
 *
 *      Author: William Posey
 *      Course: CDA 5155
 *      Project 1: MIPS Disassembler
 *
 *      This class is used to read command line input,
 *      as well as the input binary file holding the 32 bit
 *      MIPS instructions
 **************************************************************/
#include "MIPSinput.h"
#include <cstdlib>
#include <iostream>
#include <fstream>

using namespace std;

/**************************************************************
 * 		Method:			MIPSinput Destructor
 *
 * 		Parameters:
 * 		Return:
 * 		Description:	Frees the memory allocated to
 * 						the instructions pointer
 **************************************************************/
MIPSinput::~MIPSinput()
{
	//delete instructions;
}

/******************************************************************************
 * 		Method:			MIPSinput::ParseInput
 *
 * 		Parameters:		int		optionCount: Number of command line options
 * 						char**	options: command line options
 * 		Return:			if no errors present, returns true
 * 		Description:	Parses the command line options, checking for correctness
 ******************************************************************************/
bool MIPSinput::ParseInput(int optionCount, char** options)
{
	int traceSeparator;
	errorOccured = false;

	if(optionCount < 4 || optionCount > 5)
	{
		errorMessage = "ERROR: Incorrect number of command line options";
		errorOccured = true;
		return false;
	}

	inputFileName = string(options[IN_FILENAME_INDEX]);
	outputFileName = string(options[OUT_FILENAME_INDEX]);
	operation = string(options[OPERATION_INDEX]);
	if( (operation.compare("dis") != 0) && (operation.compare("sim") != 0) )
	{
		errorMessage = "ERROR: Incorrect operation";
		errorOccured = true;
		return false;
	}

	if(optionCount == 5)
	{
		traceOption = string(options[TRACE_OPT_INDEX]);
		traceOptionPresent = true;
		traceSeparator = traceOption.find(':');
		traceStart = atoi( traceOption.substr(2, (traceSeparator - 2)).c_str() );
		traceEnd = atoi( traceOption.substr(traceSeparator+1, (traceOption.size() - 1)).c_str() );
	}
	else
		traceOptionPresent = false;

	return true;
}

/******************************************************************************
 * 		Method:			MIPSinput::ParseBinaryFile
 *
 * 		Parameters:
 * 		Return:
 * 		Description:
 ******************************************************************************/
void MIPSinput::ParseBinaryFile()
{
	//ifstream binStream (inputFileName.c_str(), ios::binary);
}

/******************************************************************************
 * 		Method:			MIPSinput::PrintError
 *
 * 		Parameters:
 * 		Return:
 * 		Description:	Prints the error message defined by ParseInput()
 ******************************************************************************/
void MIPSinput::PrintError()
{
	if(errorOccured)
		cout << errorMessage << endl;
}


