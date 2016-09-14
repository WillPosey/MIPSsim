/************************************************
 * 		MIPSdecoder.h
 *
 *      Author: William Posey
 *      Course: CDA 5155
 *      Project 1: MIPS Disassembler
 ************************************************/

#ifndef MIPSDECODER_H_
#define MIPSDECODER_H_

#include "MIPSdefs.h"
#include <string>
#include <vector>

using namespace std;

class MIPSdecoder {
public:
	MIPSdecoder(vector<string> instructions);
	virtual ~MIPSdecoder();
	void Disassemble();
	vector<Instruction_Info> GetResults();

private:
    vector<Instruction_Info> MIPS_Instructions;
    int numInstructions;
    void AssignBitGroups();

};

#endif /* MIPSDECODER_H_ */
