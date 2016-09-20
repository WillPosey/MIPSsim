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
#include <iostream>

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
    uint32_t dataValue;

    while(ID_instance->memoryLocations.ReadBuffer(mem))
    {
        output.dataString = mem.content.binaryString;
        dataValue = mem.content.binaryValue;
        bool negative = ( dataValue & (1<<31) );
        if(negative)
        {
            oStr << "-";
            dataValue = (~dataValue) + 1;
        }
        oStr << dataValue;
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
            output.dataString = ID_instance->GetBitGroups(output.dataString);
            opcode = ID_instance->GetOpcode(mem.content.binaryString);
            mem.instruction.type = ID_instance->GetInstructionType(opcode);
            name = ID_instance->GetInstructionName(mem);
            mem.instruction.instructionString = name;
            ID_instance->CheckIfDataRegion(name, dataRegion);
            ID_instance->CompleteInstructionString(mem);
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
 * 		Method:			InstructionDecode::GetBitGroups
 *
 * 		Parameters:
 * 		Return:
 * 		Description:
 ******************************************************************************************/
string InstructionDecode::GetBitGroups(string binaryString)
{
    stringstream oStr;
    oStr <<     binaryString.substr(0,6)  + " "
            +   binaryString.substr(6,5)  + " "
            +   binaryString.substr(11,5) + " "
            +   binaryString.substr(16,5) + " "
            +   binaryString.substr(21,5) + " "
            +   binaryString.substr(26,6);
    return oStr.str();
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
            specialInstr = GetSpecialInstructionName(mem.content.binaryString.substr(26,6));
            if(!specialInstr.compare("SLL"))
                if(mem.content.binaryValue == 0)
                    specialInstr = "NOP";
            return specialInstr;
    }
    return " ";
}

/******************************************************************************************
 * 		Method:			InstructionDecode::CompleteInstructionString
 *
 * 		Parameters:
 * 		Return:
 * 		Description:
 ******************************************************************************************/
void InstructionDecode::CompleteInstructionString(MemoryLocation &mem)
{
    string restOfInstruction, instructionName;
    uint32_t binaryValue;

    instructionName = mem.instruction.instructionString;
    binaryValue = mem.content.binaryValue;
    switch(mem.instruction.type)
    {
        case MEMORY:
            restOfInstruction = " " + GetRegister((binaryValue & MEMORY_RT_MASK)>>MEMORY_RT_SHIFT) + ", "
                                    + GetMemoryOffset(binaryValue & MEMORY_OFFSET_MASK) + "("
                                    + GetRegister((binaryValue & MEMORY_BASE_MASK)>>MEMORY_BASE_SHIFT) + ")";
            break;
        case IMMEDIATE:
            restOfInstruction = " " + GetRegister((binaryValue & IMMEDIATE_RT_MASK)>>IMMEDIATE_RT_SHIFT) + ", "
                                    + GetRegister((binaryValue & IMMEDIATE_RS_MASK)>>IMMEDIATE_RS_SHIFT) + ", ";
            if(!instructionName.compare("ADDIU"))
                restOfInstruction += GetImmediateValue((binaryValue & IMMEDIATE_VALUE_MASK),true);
            else
                restOfInstruction += GetImmediateValue(binaryValue & IMMEDIATE_VALUE_MASK);
            break;
        case BRANCH:
            restOfInstruction = " " + GetRegister((binaryValue & BRANCH_RS_MASK)>>BRANCH_RS_SHIFT) + ", ";
            if( !instructionName.compare("BEQ") || !instructionName.compare("BNE") )
                restOfInstruction += GetRegister((binaryValue & BRANCH_RT_MASK)>>BRANCH_RT_SHIFT) + ", ";
            restOfInstruction += "#" + GetBranchOffset(binaryValue & BRANCH_OFFSET_MASK);
            break;
        case JUMP:
            restOfInstruction = " " + GetJumpAddress(binaryValue & JUMP_TARGET_MASK);
            break;
        case REGIMM:
            restOfInstruction = " " + GetRegister((binaryValue & REGIMM_RS_MASK)>>REGIMM_RS_SHIFT) + ", #"
                                    + GetBranchOffset(binaryValue & REGIMM_OFFSET_MASK);
            break;
        case SPECIAL:
            if( !instructionName.compare("BREAK") || !instructionName.compare("NOP") )
                break;
            restOfInstruction = " " + GetRegister((binaryValue & SPECIAL_RD_MASK)>>SPECIAL_RD_SHIFT) + ", ";
            if( instructionName.compare("SLL") && instructionName.compare("SRL") && instructionName.compare("SRA") )
                restOfInstruction += GetRegister((binaryValue & SPECIAL_RS_MASK)>>SPECIAL_RS_SHIFT) + ", ";
            restOfInstruction += GetRegister((binaryValue & SPECIAL_RT_MASK)>>SPECIAL_RT_SHIFT);
            if( !instructionName.compare("SLL") || !instructionName.compare("SRL") || !instructionName.compare("SRA") )
                restOfInstruction += ", #" + GetShiftAmount((binaryValue & SPECIAL_SA_MASK)>>SPECIAL_SA_SHIFT);
            break;
        default:
            restOfInstruction = "";
            break;
    }
    mem.instruction.instructionString += restOfInstruction;
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
string InstructionDecode::GetRegister(uint8_t regVal)
{
    return registerNames[regVal];
}

/******************************************************************************************
 * 		Method:			InstructionDecode::GetJumpAddress
 *
 * 		Parameters:
 * 		Return:
 * 		Description:
 ******************************************************************************************/
string InstructionDecode::GetJumpAddress(uint32_t address)
{
    stringstream oStr;
    oStr << "#";
    address = address * 4;
    oStr << address;
    return oStr.str();
}

/******************************************************************************************
 * 		Method:			InstructionDecode::GetShiftAmount
 *
 * 		Parameters:
 * 		Return:
 * 		Description:
 ******************************************************************************************/
string InstructionDecode::GetShiftAmount(uint8_t binary)
{
    stringstream oStr;
    oStr << (unsigned short)binary;
    return oStr.str();
}

/******************************************************************************************
 * 		Method:			InstructionDecode::GetImmediateValue
 *
 * 		Parameters:
 * 		Return:
 * 		Description:
 ******************************************************************************************/
string InstructionDecode::GetImmediateValue(uint16_t binary, bool unsignedValue)
{
    stringstream oStr;
    oStr << "#";
    bool negative = ( binary & (1<<15) );
    if(negative && !unsignedValue)
    {
        oStr << "-";
        binary = (~binary) + 1;
        oStr << binary;
    }
    else
        oStr << binary;
    return oStr.str();
}

/******************************************************************************************
 * 		Method:			InstructionDecode::GetOffset
 *
 * 		Parameters:
 * 		Return:
 * 		Description:
 ******************************************************************************************/
string InstructionDecode::GetMemoryOffset(uint16_t binary)
{
    stringstream oStr;
    bool negative = ( binary & (1<<15) );
    if(negative)
    {
        oStr << "-";
        binary = (~binary) + 1;
    }
    oStr << binary;
    return oStr.str();
}

/******************************************************************************************
 * 		Method:			InstructionDecode::GetOffset
 *
 * 		Parameters:
 * 		Return:
 * 		Description:
 ******************************************************************************************/
string InstructionDecode::GetBranchOffset(uint16_t binary)
{
    stringstream oStr;
    bool negative = ( binary & (1<<15) );
    if(negative)
    {
        oStr << "-";
        binary = (~binary) + 1;
    }
    binary*=4;
    oStr << binary;
    return oStr.str();
}

