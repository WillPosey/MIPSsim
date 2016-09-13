/************************************************
 * 		MIPSdisassembler.cpp
 *
 *      Author: William Posey
 *      Course: CDA 5155
 *      Project 1: MIPS Disassembler
 ************************************************/
#include "MIPSinput.h"
#include <iostream>

/**************************************************************
 * 		MIPS Disassembler Main Method
 **************************************************************/
int main(int argc, char** argv)
{
	MIPSinput input;
	if( ! input.ParseInput(argc, argv) )
	{
		input.PrintError();
		return 0;
	}

	std::cout << "input: " << input.GetInputFilename() << std::endl;
	std::cout << "output: " << input.GetOutputFilename() << std::endl;
	std::cout << "operation: " << input.GetOperation() << std::endl;
	if(input.IsTraceOptPresent())
	{
		std::cout << "trace start: " << input.GetTraceStart() << std::endl;
		std::cout << "trace end: " << input.GetTraceEnd() << std::endl;
	}

	return 0;
}



