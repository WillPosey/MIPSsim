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
	MIPSdecoder(vector<BinaryInfo> binaryInput);
	virtual ~MIPSdecoder(){}

	void Disassemble();
	vector<MemoryLocation> GetResults();

private:
    vector<MemoryLocation> memoryLocations;
    int numLocations;
};

#endif /* MIPSDECODER_H_ */
