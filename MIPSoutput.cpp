/***********************************************************************************
 * 		MIPSoutput.cpp
 *
 *      Author: William Posey
 *      Course: CDA 5155
 *      Project 1: MIPS Disassembler
 *
 *      This class is used to write the disassembled MIPS instructions and data.
 *      It utilizes a thread to read the MIPS_Buffer written to from the
 *      InstructionDecode stage and write to the output file
 ***********************************************************************************/
#include "MIPSoutput.h"

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>

using namespace std;

/***************************************************************************************************
 * 		Method:			writeOutput
 *
 * 		Parameters:     void*: MIPSoutput object
 * 		Return:
 * 		Description:    reads MIPS_Buffer containing output information and writes to output file
 ***************************************************************************************************/
void* writeOutput(void* object)
{
    MIPSoutput* outputInstance = (MIPSoutput*) object;
	OutputData data;

	ofstream outStream;
	outStream.open( outputInstance->filename.c_str() );
	while(outputInstance->outputInfo.ReadBuffer(data))
	{
        outStream << data.dataString + " " + data.addressString + " ";
        if(data.locationType == DATA_ADDRESS)
            outStream << data.valueString << "\r\n";
        else
            outStream << data.instructionString << "\r\n";
        outStream.flush();
	}
	outStream.close();
	return NULL;
}


