/**************************************************************
 * 		InstructionFetch.cpp
 *
 *      Author: William Posey
 *      Course: CDA 5155
 *      Project 1: MIPS Disassembler
 **************************************************************/
#include "InstructionFetch.h"

#include <iostream>

using namespace std;

/******************************************************************************************
 * 		Method:			readBinaries
 *
 * 		Parameters:
 * 		Return:
 * 		Description:
 ******************************************************************************************/
void* readBinaries(void* object)
{
    InstructionFetch* IF_instance = (InstructionFetch*) object;

    BinaryInfo binary;

    // initialize a MemoryLocation structure
    MemoryLocation currentLocation;
    currentLocation.address = ADDRESS_START-INSTRUCTION_SIZE_BYTES;

    while(IF_instance->binaries.ReadBuffer(binary))
    {
        currentLocation.address += INSTRUCTION_SIZE_BYTES;
        currentLocation.content = binary;
        IF_instance->memoryLocations.WriteBuffer(currentLocation);
    }

    IF_instance->memoryLocations.WriterComplete();

    return NULL;
}
