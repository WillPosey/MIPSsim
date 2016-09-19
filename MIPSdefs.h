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

#include <string>
#include <vector>
#include <stdint.h>

using namespace std;

// the bit length of each component for each instruction type
static const int memoryBitIntervals[]       = {6,5,5,16};
static const int immediateBitIntervals[]    = {6,5,5,16};
static const int branchBitIntervals[]       = {6,5,5,16};
static const int jumpBitIntervals[]         = {6,26};
static const int regimmBitIntervals[]       = {6,5,5,16};
static const int specialBitIntervals[]      = {6,5,5,5,5,6};

// number of components for each instruction type, indexable by the InstructionType enumeration
static const int componentSizes[]           = {4,4,4,2,4,6};

// array of all bit interval, indexable by the InstructionType enumeration
static const int* bitIntervals[] = {
                                        memoryBitIntervals,
                                        immediateBitIntervals,
                                        branchBitIntervals,
                                        jumpBitIntervals,
                                        regimmBitIntervals,
                                        specialBitIntervals
                                   };

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

/* Holds the information regarding the different components of an instruction */
typedef struct
{
    vector<int>         bitIntervals;
    vector<string>      componentNames;
    vector<uint32_t>    componentValues;
    vector<int>         componentLengths;
} InstructionComponents;

/* Holds the information for each instruction */
typedef struct
{
    string                  instructionString;
    InstructionType         type;
    InstructionComponents   components;
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
