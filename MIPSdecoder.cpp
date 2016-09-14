/**************************************************************
 * 		MIPSdecoder.cpp
 *
 *      Author: William Posey
 *      Course: CDA 5155
 *      Project 1: MIPS Disassembler
 *
 *      This class is used to disassemble the instructions read
 *      from a binary input file
 **************************************************************/
#include "MIPSdecoder.h"
#include "MIPSdefs.h"
#include <cstring>
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

/******************************************************************************************
 * 		Method:			MIPSdecoder Constructor
 *
 * 		Parameters:     vector<string> instructions: contains all input instructions
 * 		Return:
 * 		Description:    The MIPSdecoder constructor initializes a vector of Instruction_Info
 *                      structs with the 32 bit instructions as strings, and both an integer
 *                      and string representation of the corresponding instruction address
 ******************************************************************************************/
MIPSdecoder::MIPSdecoder(vector<string> instructions)
{
    ostringstream ostr;
    string tempAddress;

    // initialize a Instruction_Info structure
    Instruction_Info tempInfo;
    memset(&tempInfo, 0, sizeof(tempInfo));
    tempInfo.address = ADDRESS_START-INSTRUCTION_SIZE_BYTES;

    // store an Instruction_Info struct in the MIPS_Instructions vector
    // for each input instruction
    numInstructions = instructions.size();
    for(int i=0; i<numInstructions; i++)
    {
        if(i)
            tempInfo.binaryInstruction.clear();
        tempInfo.address += INSTRUCTION_SIZE_BYTES;
        ostr.str("");
        ostr << tempInfo.address;
        tempInfo.addressString = ostr.str();
        tempInfo.binaryInstruction = instructions[i];
        MIPS_Instructions.push_back(tempInfo);
    }
}

/**************************************************************
 * 		Method:			MIPSdecoder Destructor
 *
 * 		Parameters:
 * 		Return:
 * 		Description:
 **************************************************************/
MIPSdecoder::~MIPSdecoder()
{
}

/**************************************************************
 * 		Method:			MIPSdecoder Disassemble
 *
 * 		Parameters:
 * 		Return:
 * 		Description:
 **************************************************************/
void MIPSdecoder::Disassemble()
{
    AssignBitGroups();
    for(int i=0; i < numInstructions; i++)
    cout << MIPS_Instructions[i].bitGroup_1 + " "
            + MIPS_Instructions[i].bitGroup_2 + " "
            + MIPS_Instructions[i].bitGroup_3 + " "
            + MIPS_Instructions[i].bitGroup_4 + " "
            + MIPS_Instructions[i].bitGroup_5 + " "
            + MIPS_Instructions[i].bitGroup_6 + " "
            + MIPS_Instructions[i].addressString << endl;
}

/**************************************************************
 * 		Method:			MIPSdecoder AssignBitGroups
 *
 * 		Parameters:
 * 		Return:
 * 		Description:    Breaks apart the 32 bit instruction into
 *                      the following groups:
 *                      6 bits (bits 31 to 26)
 *                      5 bits (bits 25 to 21)
 *                      5 bits (bits 20 to 16)
 *                      5 bits (bits 15 to 11)
 *                      5 bits (bits 10 to  6)
 *                      6 bits (bits  5 to  0)
 **************************************************************/
void MIPSdecoder::AssignBitGroups()
{

    for(int i=0; i < numInstructions; i++)
    {
        MIPS_Instructions[i].bitGroup_1 = MIPS_Instructions[i].binaryInstruction.substr(0,6);
        MIPS_Instructions[i].bitGroup_2 = MIPS_Instructions[i].binaryInstruction.substr(6,5);
        MIPS_Instructions[i].bitGroup_3 = MIPS_Instructions[i].binaryInstruction.substr(11,5);
        MIPS_Instructions[i].bitGroup_4 = MIPS_Instructions[i].binaryInstruction.substr(16,5);
        MIPS_Instructions[i].bitGroup_5 = MIPS_Instructions[i].binaryInstruction.substr(21,5);
        MIPS_Instructions[i].bitGroup_6 = MIPS_Instructions[i].binaryInstruction.substr(26,6);
    }
}


