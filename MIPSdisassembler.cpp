/************************************************
 * 		MIPSdisassembler.cpp
 *
 *      Author: William Posey
 *      Course: CDA 5155
 *      Project 1: MIPS Disassembler
 ************************************************/
#include "MIPSinput.h"
#include "MIPS_Buffer.h"
#include "InstructionFetch.h"
#include "InstructionDecode.h"
#include "MIPSdefs.h"
#include <iostream>

/**************************************************************
 * 		MIPS Disassembler Main Method
 **************************************************************/
int main(int argc, char** argv)
{
    /*for(int i=0; i<NUM_INSTRUCTION_TYPES; i++)
    {
        for(int j=0; j<bitIntervalSizes[i]; j++)
            cout << bitIntervals[i][j] << " ";
        cout << endl;
    }*/

    MIPS_Buffer<BinaryInfo> binaries;
    MIPS_Buffer<MemoryLocation> memoryLocations;
    MIPS_Buffer<OutputData> disassembled;

	MIPSinput input (binaries);
	InstructionFetch IF (binaries, memoryLocations);
	InstructionDecode ID (memoryLocations, disassembled);
	//MIPSoutput output (disassembled);

	if( ! input.ParseInput(argc, argv) )
	{
		input.PrintError();
		return 0;
	}

	input.ParseBinaryFile();
	IF.GetInstructions();
	ID.Decode();
	OutputData info;
    while(disassembled.ReadBuffer(info))
    {
        cout << info.dataString + " " + info.addressString + " ";
        if(info.locationType == DATA_ADDRESS)
            cout << info.valueString << endl;
        else
            cout << info.instructionString << endl;
    }
	//output.WriteResults();
	//output.WaitForCompletion();

	return 0;
}



