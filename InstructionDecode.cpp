/**************************************************************
 * 		InstructionDecode.cpp
 *
 *      Author: William Posey
 *      Course: CDA 5155
 *      Project 1: MIPS Disassembler
 **************************************************************/
#include "InstructionDecode.h"
#include "MIPSdefs.h"

#include <sstream>

using namespace std;

/******************************************************************************************
 * 		Method:			decodeInstructions
 *
 * 		Parameters:
 * 		Return:
 * 		Description:
 ******************************************************************************************/
void* decodeInstructions(void* object)
{
    InstructionDecode* ID_instance = (InstructionDecode*) object;

    MemoryLocation mem;
    OutputData output;
    string opcode, name;
    stringstream oStr;
    bool dataRegion = false;

    while(ID_instance->memoryLocations.ReadBuffer(mem))
    {
        output.dataString = mem.content.binaryString;
        oStr << mem.content.binaryValue;
        output.valueString = oStr.str();
        oStr.str("");
        oStr << mem.address;
        output.addressString = oStr.str();
        oStr.str("");
        output.instructionString = "";
        if(dataRegion)
            mem.locationType = output.locationType = DATA_ADDRESS;
        else
        {
            mem.locationType = output.locationType = INSTRUCTION_ADDRESS;
            oStr <<     output.dataString.substr(0,6) + " "
                    +   output.dataString.substr(6,5) + " "
                    +   output.dataString.substr(11,5) + " "
                    +   output.dataString.substr(16,5) + " "
                    +   output.dataString.substr(21,5) + " "
                    +   output.dataString.substr(26,6);
            output.dataString = oStr.str();
            oStr.str("");
            opcode = ID_instance->GetOpcode(mem.content.binaryString);
            mem.instruction.type = ID_instance->GetInstructionType(opcode);
            name = ID_instance->GetInstructionName(mem);
            mem.instruction.instructionString = name;
            if(!name.compare(instructionNames[SPECIAL][BREAK]))
                dataRegion = true;
            opcode.clear();
            name.clear();
            output.instructionString = mem.instruction.instructionString;
        }
        ID_instance->output.WriteBuffer(output);
    }
    ID_instance->output.WriterComplete();
    return NULL;
}

/******************************************************************************************
 * 		Method:			InstructionDecode::GetInstructionType
 *
 * 		Parameters:
 * 		Return:
 * 		Description:
 ******************************************************************************************/
InstructionType InstructionDecode::GetInstructionType(string opcode)
{
    if(opcode[0] == '1')
        return MEMORY;
    if(opcode[2] == '1')
        return IMMEDIATE;
    if(opcode[3] == '1')
        return BRANCH;
    if(opcode[4] == '1')
        return JUMP;
    if(opcode[5] == '1')
        return REGIMM;
    return SPECIAL;
}

/******************************************************************************************
 * 		Method:			InstructionDecode::GetInstructionComponents
 *
 * 		Parameters:
 * 		Return:
 * 		Description:
 ******************************************************************************************/
void InstructionDecode::GetInstructionComponents(MemoryLocation &mem)
{

}

/******************************************************************************************
 * 		Method:			InstructionDecode::GetInstructionName
 *
 * 		Parameters:
 * 		Return:
 * 		Description:
 ******************************************************************************************/
string InstructionDecode::GetInstructionName(MemoryLocation mem)
{
    string specialInstr, opcode;
    opcode = GetOpcode(mem.content.binaryString);
    switch(mem.instruction.type)
    {
        case MEMORY:
            return GetMemoryInstructionName(opcode);
        case IMMEDIATE:
            return GetImmediateInstructionName(opcode);
        case BRANCH:
            return GetBranchInstructionName(opcode);
        case JUMP:
            return GetJumpInstructionName();
        case REGIMM:
            return GetRegimmInstructionName(mem.content.binaryString.substr(11,5));
        case SPECIAL:
            specialInstr = GetSpecialInstructionName(mem.content.binaryString.substr(26,5));
            if(!specialInstr.compare("SLL"))
                if(mem.content.binaryValue == 0)
                    specialInstr = "NOP";
            return specialInstr;
    }
    return " ";
}

/******************************************************************************************
 * 		Method:			InstructionDecode::GetMemoryInstructionName
 *
 * 		Parameters:
 * 		Return:
 * 		Description:
 ******************************************************************************************/
string InstructionDecode::GetMemoryInstructionName(string opcode)
{
    if(opcode[2] == '1')
        return instructionNames[MEMORY][SW];
    else
        return instructionNames[MEMORY][LW];
}

/******************************************************************************************
 * 		Method:			InstructionDecode::GetImmediateInstructionName
 *
 * 		Parameters:
 * 		Return:
 * 		Description:
 ******************************************************************************************/
string InstructionDecode::GetImmediateInstructionName(string opcode)
{
    if(opcode[4] == '1')
        return instructionNames[IMMEDIATE][SLTI];
    else if(opcode[5] == '1')
        return instructionNames[IMMEDIATE][ADDIU];
    else
        return instructionNames[IMMEDIATE][ADDI];
}

/******************************************************************************************
 * 		Method:			InstructionDecode::GetBranchInstructionName
 *
 * 		Parameters:
 * 		Return:
 * 		Description:
 ******************************************************************************************/
string InstructionDecode::GetBranchInstructionName(string opcode)
{
    if(opcode[4] == '1')
    {
        if(opcode[5] == '1')
            return instructionNames[BRANCH][BGTZ];
        else
            return instructionNames[BRANCH][BLEZ];
    }
    else if(opcode[5] == '1')
        return instructionNames[BRANCH][BNE];
    else
        return instructionNames[BRANCH][BEQ];
}

/******************************************************************************************
 * 		Method:			InstructionDecode::GetJumpInstructionName
 *
 * 		Parameters:
 * 		Return:
 * 		Description:
 ******************************************************************************************/
string InstructionDecode::GetJumpInstructionName()
{
    return instructionNames[JUMP][J];
}

/******************************************************************************************
 * 		Method:			InstructionDecode::GetRegimmInstructionName
 *
 * 		Parameters:
 * 		Return:
 * 		Description:
 ******************************************************************************************/
string InstructionDecode::GetRegimmInstructionName(string funct)
{
    if(funct[4] == '1')
        return instructionNames[REGIMM][BGEZ];
    else
        return instructionNames[REGIMM][BLTZ];
}

/******************************************************************************************
 * 		Method:			InstructionDecode::GetSpecialInstructionName
 *
 * 		Parameters:
 * 		Return:
 * 		Description:
 ******************************************************************************************/
string InstructionDecode::GetSpecialInstructionName(string funct)
{
    if(funct[0] == '1')
    {
        if(funct[2] == '1')
        {
            if(funct[5] == '1')
                return instructionNames[SPECIAL][SLTU];
            else
                return instructionNames[SPECIAL][SLT];
        }
        else if(funct[3] == '1')
        {
            if(funct[4] == '1')
            {
                if(funct[5] == '1')
                    return instructionNames[SPECIAL][NOR];
                else
                    return instructionNames[SPECIAL][XOR];

            }
            else if(funct[5] == '1')
                return instructionNames[SPECIAL][OR];
            else
                return instructionNames[SPECIAL][AND];
        }
        else if(funct[4] == '1')
        {
            if(funct[5] == '1')
                return instructionNames[SPECIAL][SUBU];
            else
                return instructionNames[SPECIAL][SUB];
        }
        else
        {
            if(funct[5] == '1')
                return instructionNames[SPECIAL][ADDU];
            else
                return instructionNames[SPECIAL][ADD];
        }
    }
    else if(funct[2] == '1')
        return instructionNames[SPECIAL][BREAK];
    else if(funct[4] == '1')
    {
        if(funct[5] == '1')
            return instructionNames[SPECIAL][SRA];
        else
            return instructionNames[SPECIAL][SRL];
    }
    else
        return instructionNames[SPECIAL][SLL];
}

/******************************************************************************************
 * 		Method:			InstructionDecode::GetRegister
 *
 * 		Parameters:
 * 		Return:
 * 		Description:
 ******************************************************************************************/
string InstructionDecode::GetRegister(uint32_t regVal)
{
    return "hi";
}

/******************************************************************************************
 * 		Method:			InstructionDecode::GetShiftAmount
 *
 * 		Parameters:
 * 		Return:
 * 		Description:
 ******************************************************************************************/
string InstructionDecode::GetShiftAmount(uint32_t binary)
{
    return "hi";
}

/******************************************************************************************
 * 		Method:			InstructionDecode::GetImmediateValue
 *
 * 		Parameters:
 * 		Return:
 * 		Description:
 ******************************************************************************************/
string InstructionDecode::GetImmediateValue(uint32_t binary)
{
    return "hi";
}

/******************************************************************************************
 * 		Method:			InstructionDecode::GetOffset
 *
 * 		Parameters:
 * 		Return:
 * 		Description:
 ******************************************************************************************/
string InstructionDecode::GetOffset(uint32_t binary)
{
    return "hi";
}

