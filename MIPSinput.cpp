/**************************************************************
 * 		MIPSinput.cpp
 *
 *      Author: William Posey
 *      Course: CDA 5155
 *      Project 1: MIPS Disassembler
 *
 *      This class is used to read command line input,
 *      as well as the input binary file holding the 32 bit
 *      MIPS instructions and data
 **************************************************************/
#include "MIPSinput.h"

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>

using namespace std;

/******************************************************************************
 * 		Method:			MIPSinput::ParseInput
 *
 * 		Parameters:		int: Number of command line options
 * 						char**: command line options
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
 * 		Method:			readInput
 *
 * 		Parameters:     void*: the MIPSinput object
 * 		Return:
 * 		Description:    work function supplied to WorkThread member
 *                      reads binaries from input file and writes to the buffer
 ******************************************************************************/
void* readInput(void* object)
{
    MIPSinput* inputInstance = (MIPSinput*) object;
    int sizeBytes;
	streampos start, finish;
	uint8_t byte;
	BinaryInfo content;
	char currentInstruction[33], bitVal;

	// Open the binary input file, get its size, and determine
	// the number of instructions. Read in each instruction to a uint32_t
	ifstream binStream (inputInstance->inputFileName.c_str(), ios::binary);
	if(binStream)
	{
        memset(currentInstruction, 0, 33);
		start = binStream.tellg();
		binStream.seekg(0, ios::end);
		finish = binStream.tellg();
		sizeBytes = finish - start;
		inputInstance->numLocations = sizeBytes / 4.0;
		binStream.seekg(0, ios::beg);
		for(int i=0; i<inputInstance->numLocations; i++)
		{
            // reset BinaryInfo structure
            if(i)
                content.binaryString.clear();
			content.binaryValue = 0;

			// read the binary value
			for(int j=3; j>=0; j--)
			{
				binStream.read((char*)&byte, 1);
				content.binaryValue |= (byte<<(j*8));
			}

			// convert binary value into a string
			int index = 0;
			for(int bit=31; bit>=0; bit--)
			{
				bitVal = ( content.binaryValue & (1<<bit) ) ? '1' : '0';
				currentInstruction[index++] = bitVal;
			}
			content.binaryString = string(currentInstruction);

			// write the BinaryInfo to the MIPS_Buffer
			inputInstance->binaries.WriteBuffer(content);
        }
		binStream.close();
		inputInstance->binaries.WriterComplete();
	}
	return NULL;
}


