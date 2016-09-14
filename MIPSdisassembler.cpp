/************************************************
 * 		MIPSdisassembler.cpp
 *
 *      Author: William Posey
 *      Course: CDA 5155
 *      Project 1: MIPS Disassembler
 ************************************************/
#include "MIPSinput.h"
#include "MIPSdecoder.h"
#include <iostream>

/**************************************************************
 * 		MIPS Disassembler Main Method
 **************************************************************/
int main(int argc, char** argv)
{
	MIPSinput	input;
	//MIPSoutput	output;

	if( ! input.ParseInput(argc, argv) )
	{
		input.PrintError();
		return 0;
	}

	input.ParseBinaryFile();

	MIPSdecoder	decoder (input.GetInstructionStrings());
	decoder.Disassemble();

	return 0;
}



