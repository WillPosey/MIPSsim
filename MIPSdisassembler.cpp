/************************************************
 * 		MIPSdisassembler.cpp
 *
 *      Author: William Posey
 *      Course: CDA 5155
 *      Project 1: MIPS Disassembler
 ************************************************/
#include "MIPSinput.h"
#include "MIPSoutput.h"
#include "MIPS_Buffer.h"
#include "InstructionFetch.h"
#include "InstructionDecode.h"
#include "MIPSdefs.h"

/**************************************************************
 * 		MIPS Disassembler Main Method
 **************************************************************/
int main(int argc, char** argv)
{
    MIPS_Buffer<BinaryInfo> binaries;
    MIPS_Buffer<MemoryLocation> memoryLocations;
    MIPS_Buffer<OutputData> disassembled;

	MIPSinput input (binaries);
	if( ! input.ParseInput(argc, argv) )
	{
		input.PrintError();
		return 0;
	}

	InstructionFetch IF (binaries, memoryLocations);
	InstructionDecode ID (memoryLocations, disassembled);
	MIPSoutput output (disassembled, input.GetOutputFilename());

	input.ParseBinaryFile();
	IF.GetInstructions();
	ID.Decode();
	output.WriteResults();
	output.thread->JoinThread();

	return 0;
}



