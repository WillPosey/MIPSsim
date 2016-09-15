/************************************************
 * 		MIPSdefs.h
 *
 *      Author: William Posey
 *      Course: CDA 5155
 *      Project 1: MIPS Disassembler
 ************************************************/

#ifndef MIPSDEFS_H_
#define MIPSDEFS_H_

#define INSTRUCTION_SIZE_BYTES 4

#define ADDRESS_START 600
#define DATA_REGION_START 716

#include <string>
#include <stdint.h>

using namespace std;

/* Holds the binary information for each memory location */
typedef struct BinaryInfo_t
{
    uint32_t    binaryValue;
    string      binaryString;
} BinaryInfo;

/* Holds the information for each memory location, either instruction or data memory */
typedef struct MemoryLocation_t
{
    uint8_t     locationType;
    int         address;
    BinaryInfo  content;
    string      instruction;
} MemoryLocation;

#endif //MIPSDEFS_H_
