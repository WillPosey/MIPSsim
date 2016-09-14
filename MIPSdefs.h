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

#include <string>

using namespace std;

typedef struct Instruction_Info_t
{
    string  binaryInstruction;
    string  disassembledInstruction;
    string  bitGroup_1;
    string  bitGroup_2;
    string  bitGroup_3;
    string  bitGroup_4;
    string  bitGroup_5;
    string  bitGroup_6;
    string  addressString;
    int     address;
    int     breakPoint;
} Instruction_Info;

#endif //MIPSDEFS_H_
