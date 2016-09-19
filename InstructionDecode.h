/************************************************
 * 		InstructionDecode.h
 *
 *      Author: William Posey
 *      Course: CDA 5155
 *      Project 1: MIPS Disassembler
 ************************************************/

#ifndef INSTRUCTION_DECODE_H
#define INSTRUCTION_DECODE_H

#include "MIPSdefs.h"
#include "MIPS_Buffer.h"
#include "WorkThread.h"

#include <stdint.h>

using namespace std;

// used for WorkThread thread function
void* decodeInstructions(void*);

class InstructionDecode {
public:
    friend void* decodeInstructions(void*);
	InstructionDecode(  MIPS_Buffer<MemoryLocation> &mem,
                        MIPS_Buffer<OutputData> &out
                    ) : memoryLocations(mem), output(out)
                    {thread = new WorkThread(decodeInstructions, (void*) this);}
	virtual ~InstructionDecode(){}

	void Decode(){thread->Activate();}

private:
    // Buffers used to read memory location info from InstructionFetch
    // and write output data for MIPSoutput
    MIPS_Buffer<MemoryLocation> &memoryLocations;
    MIPS_Buffer<OutputData> &output;

	// WorkThread used to carry out the retrieval of the binary input
	WorkThread* thread;

	// Methods used to decode the instructions
	string GetOpcode(string binaryString){return binaryString.substr(0,6);}
	InstructionType GetInstructionType(string opcode);
	void GetInstructionComponents(MemoryLocation &mem);
	string GetInstructionName(MemoryLocation mem);
	string GetMemoryInstructionName(string opcode);
	string GetImmediateInstructionName(string opcode);
	string GetBranchInstructionName(string opcode);
	string GetJumpInstructionName();
	string GetRegimmInstructionName(string funct);
	string GetSpecialInstructionName(string funct);
	string GetRegister(uint32_t regVal);
	string GetShiftAmount(uint32_t binary);
	string GetImmediateValue(uint32_t binary);
	string GetOffset(uint32_t binary);
};

#endif /* INSTRUCTION_DECODE_H */

