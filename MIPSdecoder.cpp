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
MIPSdecoder::MIPSdecoder(vector<BinaryInfo> binaryInput)
{
    ostringstream ostr;
    string tempAddress;

    // initialize a MemoryLocation structure
    MemoryLocation currentLocation;
    currentLocation.address = ADDRESS_START-INSTRUCTION_SIZE_BYTES;

    // initialize MemoryLocation vector with binary values, binary strings, and address
    numLocations = binaryInput.size();
    for(int i=0; i<numLocations; i++)
    {
        currentLocation.address += INSTRUCTION_SIZE_BYTES;
        currentLocation.content = binaryInput[i];
        memoryLocations.push_back(currentLocation);

        cout << memoryLocations[i].content.binaryString.substr(0,6) + " "
                + memoryLocations[i].content.binaryString.substr(6,5) + " "
                + memoryLocations[i].content.binaryString.substr(11,5) + " "
                + memoryLocations[i].content.binaryString.substr(16,5) + " "
                + memoryLocations[i].content.binaryString.substr(21,5) + " "
                + memoryLocations[i].content.binaryString.substr(26,6) + " "
            << memoryLocations[i].address
            <<  endl;

    }
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
}


