/**************************************************************
 * 		MIPSoutput.cpp
 *
 *      Author: William Posey
 *      Course: CDA 5155
 *      Project 1: MIPS Disassembler
 *
 *
 **************************************************************/
#include "MIPSoutput.h"

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>

using namespace std;

/******************************************************************************
 * 		Method:			writeOutput
 *
 * 		Parameters:
 * 		Return:
 * 		Description:
 ******************************************************************************/
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
            outStream << data.valueString << endl;
        else
            outStream << data.instructionString << endl;
	}
	outStream.close();
	return NULL;
}


