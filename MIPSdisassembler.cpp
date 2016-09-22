/*******************************************************************************************************
 * 		MIPSdisassembler.cpp
 *
 *      Author: William Posey
 *      Course: CDA 5155
 *      Project 1: MIPS Disassembler
 *
 *      This program reads binary input from a file that contains 32 bit MIPS instructions,
 *      followed by 32 bit signed data, disassembles the binaries into readable MIPS assembly
 *      instructions and 32 bit signed data, and writes the disassembled information to an output file
 *******************************************************************************************************/
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
    // Buffers to hold information between disassembly stages
    // these buffers allow each stage to run in a multithreaded fashion
    // each stage runs a thread that writes/reads information to/from a buffer
    // as it interacts with each memory location from the input binaries
    //
    // (input)-->[BinaryInfo]<--(IF)-->[MemoryLocation]<--(ID)-->[OutputData]-->(output)
    //
    MIPS_Buffer<BinaryInfo> binaries;
    MIPS_Buffer<MemoryLocation> memoryLocations;
    MIPS_Buffer<OutputData> disassembled;

    // Parse the command line input
	MIPSinput input (binaries);
	if( ! input.ParseInput(argc, argv) )
	{
		input.PrintError();
		return 0;
	}

    // stages following the input stage
	InstructionFetch IF (binaries, memoryLocations);
	InstructionDecode ID (memoryLocations, disassembled);
	MIPSoutput output (disassembled, input.GetOutputFilename());

    // flow of binaries to disassembled output
	input.ParseBinaryFile();
	IF.GetInstructions();
	ID.Decode();
	output.WriteResults();

	return 0;
}



