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

#define NUM_INSTRUCTION_TYPES 6

#define DATA_ADDRESS 0
#define INSTRUCTION_ADDRESS 1

/*******************************************************/
/* Masks to access components of each instruction type */
// Memory
#define MEMORY_BASE_MASK        0x03E00000
#define MEMORY_RT_MASK          0x001F0000
#define MEMORY_OFFSET_MASK      0x0000FFFF
#define MEMORY_BASE_SHIFT       21
#define MEMORY_RT_SHIFT         16
// Immediate
#define IMMEDIATE_RS_MASK       0x03E00000
#define IMMEDIATE_RT_MASK       0x001F0000
#define IMMEDIATE_VALUE_MASK    0x0000FFFF
#define IMMEDIATE_RS_SHIFT      21
#define IMMEDIATE_RT_SHIFT      16
// Branch
#define BRANCH_RS_MASK          0x03E00000
#define BRANCH_RT_MASK          0x001F0000
#define BRANCH_OFFSET_MASK      0x0000FFFF
#define BRANCH_RS_SHIFT         21
#define BRANCH_RT_SHIFT         16
// Jump
#define JUMP_TARGET_MASK        0x03FFFFFF
// Regimm
#define REGIMM_RS_MASK          0x03E00000
#define REGIMM_OFFSET_MASK      0x0000FFFF
#define REGIMM_RS_SHIFT         21
// Special
#define SPECIAL_RS_MASK         0x03E00000
#define SPECIAL_RT_MASK         0x001F0000
#define SPECIAL_RD_MASK         0x0000F800
#define SPECIAL_SA_MASK         0x000007C0
#define SPECIAL_RS_SHIFT        21
#define SPECIAL_RT_SHIFT        16
#define SPECIAL_RD_SHIFT        11
#define SPECIAL_SA_SHIFT        6
/*******************************************************/

#include <string>
#include <vector>
#include <stdint.h>

using namespace std;

// arrays holding the instruction names for each instruction type
static const string memoryInstructionNames[]    = {"LW","SW"};
static const string immediateInstructionNames[] = {"ADDI","ADDIU","SLTI"};
static const string branchInstructionNames[]    = {"BEQ","BNE","BLEZ","BGTZ"};
static const string jumpInstructionNames[]      = {"J"};
static const string regimmInstructionNames[]    = {"BLTZ","BGEZ"};
static const string specialInstructionNames[]   = {"NOP","SLL","SRL","SRA","BREAK","ADD","ADDU","SUB","SUBU","AND","OR","XOR","NOR","SLT","SLTU"};

// array of all instruction names, indexable by the InstructionType enum
static const string* instructionNames[]         = {
                                                    memoryInstructionNames,
                                                    immediateInstructionNames,
                                                    branchInstructionNames,
                                                    jumpInstructionNames,
                                                    regimmInstructionNames,
                                                    specialInstructionNames
                                                  };

// array of the register names
static const string registerNames[]             = {
                                                    "R0","R1","R2","R3","R4","R5","R6","R7","R8","R9","R10",
                                                    "R11","R12","R13","R14","R15","R16","R17","R18","R19","R20","R21",
                                                    "R22","R23","R24","R25","R26","R27","R28","R29","R30","R31",
                                                  };

// instruction types (used for decoding)
typedef enum
{
    MEMORY,
    IMMEDIATE,
    BRANCH,
    JUMP,
    REGIMM,
    SPECIAL
} InstructionType;

// instruction names (used for indexing instructionNames array)
typedef enum
{
    LW=0,SW=1,
    ADDI=0,ADDIU=1,SLTI=2,
    BEQ=0,BNE=1,BLEZ=2,BGTZ=3,
    J=0,
    BLTZ=0,BGEZ=1,
    NOP=0,SLL=1,SRL=2,SRA=3,BREAK=4,ADD=5,ADDU=6,SUB=7,SUBU=8,AND=9,OR=10,XOR=11,NOR=12,SLT=13,SLTU=14
} instr_names;

/* Holds the binary information for each memory location */
typedef struct
{
    uint32_t    binaryValue;
    string      binaryString;
} BinaryInfo;

/* Holds the information for each instruction */
typedef struct
{
    string                  instructionString;
    InstructionType         type;
} InstructionInfo;

/* Holds the information for each memory location, either instruction or data memory */
typedef struct
{
    uint8_t         locationType;
    int             address;
    BinaryInfo      content;
    InstructionInfo instruction;
} MemoryLocation;

/* Holds the information for each memory location, either instruction or data memory */
typedef struct
{
    uint8_t         locationType;
    string          addressString;
    string          valueString;
    string          instructionString;
    string          dataString;
} OutputData;

#endif //MIPSDEFS_H_
