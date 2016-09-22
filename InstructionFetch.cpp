/*****************************************************************************************************
 * 		InstructionFetch.cpp
 *
 *      Author: William Posey
 *      Course: CDA 5155
 *      Project 1: MIPS Disassembler
 *
 *      This class reads from a MIPS_Buffer containing BinaryInfo structures,
 *      assigns the memory address and memory location type for each of the binaries,
 *      and writes the information into a MemoryLocation structure, which is written to a MIPS_Buffer
 *****************************************************************************************************/
#include "InstructionFetch.h"

#include <iostream>

using namespace std;

/******************************************************************************************************
 * 		Method:			readBinaries
 *
 * 		Parameters:     void*: InstructionFetch object
 * 		Return:
 * 		Description:    reads BinaryInfo from MIPS_Buffer, assigns address and memory location type,
 *                      writes MemoryLocation structure to second MIPS_Buffer
 ******************************************************************************************************/
void* readBinaries(void* object)
{
    InstructionFetch* IF_instance = (InstructionFetch*) object;

    BinaryInfo binary;

    // initialize a MemoryLocation structure
    MemoryLocation currentLocation;
    currentLocation.address = ADDRESS_START-INSTRUCTION_SIZE_BYTES;

    // fill out MemoryLocation structure for each binary, write to output MIPS_Buffer
    while(IF_instance->binaries.ReadBuffer(binary))
    {
        currentLocation.address += INSTRUCTION_SIZE_BYTES;
        currentLocation.content = binary;
        IF_instance->memoryLocations.WriteBuffer(currentLocation);
    }

    IF_instance->memoryLocations.WriterComplete();

    return NULL;
}
