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
	delete instructions;
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
	int sizeBytes;
	streampos start, end;
	uint8_t byte;
	char currentInstruction[32], bitVal;

	// Open the binary input file, get its size, and determine
	// the number of instructions. Read in each instruction to a uint32_t
	ifstream binStream (inputFileName.c_str(), ios::binary);
	if(binStream)
	{
		start = binStream.tellg();
		binStream.seekg(0, ios::end);
		end = binStream.tellg();
		sizeBytes = end - start;
		numInstructions = sizeBytes / 4.0;
		instructions = new uint32_t[numInstructions];
		binStream.seekg(0, ios::beg);
		for(int i=0; i<numInstructions; i++)
			for(int j=0; j<4; j++)
			{
				binStream.read((char*)&byte, 1);
				SwapBitOrder(&byte);
				instructions[i] |= (byte<<(j*8));
			}
		binStream.close();

		// Convert the binary values to strings for decoding
		for(int i=0; i<numInstructions; i++)
		{
			for(int bit=0; bit<32; bit++)
			{
				bitVal = ( instructions[i] & (1<<bit) ) ? '1' : '0';
				currentInstruction[bit] = bitVal;
			}
			instructionStrings.push_back(currentInstruction);
		}
	}
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

/******************************************************************************
 * 		Method:			MIPSinput::SwapBitOrder
 *
 * 		Parameters:		uint8_t* byte:	Byte to swap bit order for
 * 		Return:
 * 		Description:	Swaps the bit order of the input byte
 ******************************************************************************/
void MIPSinput::SwapBitOrder(uint8_t* byte)
{
	uint8_t temp = 0;
	int bitVal;
	for(int i=7, j=0; i>=0 && j<8; i--, j++)
	{
		bitVal = ( (*byte) & (1<<i) ) ? 1 : 0;
		temp |= (bitVal<<j);
	}
	*byte = temp;
}

/******************************************************************************
 * 		Method:			MIPSinput::GetBinaryInstructions
 *
 * 		Parameters:		uint32_t* binInstructions:	Pointer to hold instructions
 * 						int bufferLength: Size of the memory referenced by the pointer
 * 		Return:			0 on success, -1 if buffer too small
 * 		Description:	Returns binary instructions in uint32_t* parameter
 ******************************************************************************/
int MIPSinput::GetBinaryInstructions(uint32_t* binInstructions, int bufferLength)
{
	if(bufferLength < numInstructions)
		return -1;

	for(int i=0; i<numInstructions; i++)
		binInstructions[i] = instructions[i];

	return 0;
}


