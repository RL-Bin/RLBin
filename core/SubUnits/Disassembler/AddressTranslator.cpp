/**
 * @file AddressTranslator.cpp
 * @brief Implementation of the functions in Disassembler class which dynamically calculate the address of instructions   
 */

#include <math.h>

#include "..\..\include\SubUnits\Disassembler\Disassembler.h"
#include "..\..\include\SubUnits\Modules\Modules.h"

void Disassembler::GetDirectCTIDest(ADDRESS _address, ADDRESS *_destAddress)
{
	Inst instruction;
	GetOneInst(_address, &instruction);
	if (instruction.operands[0].type != X86_OP_IMM)
	{
		RLBinUtils::RLBin_Error("This instruction is not supported " + RLBinUtils::ConvertHexToString(instruction.address), __FILENAME__, __LINE__);
		*_destAddress = (ADDRESS)(((instruction.address + instruction.size) + instruction.disp));
	}
	else
		*_destAddress = (ADDRESS)(instruction.operands[0].imm);
}

void Disassembler::GetConditionalCTIDest(ADDRESS _address, ADDRESS *_destAddress)
{
	Inst instruction;
	GetOneInst(_address, &instruction);
	_destAddress[0] = (ADDRESS) instruction.operands[0].imm;
	_destAddress[1] = (ADDRESS) instruction.address + instruction.size;
}

void Disassembler::GetIndirectCTIDest(ADDRESS _address, ADDRESS *_destAddress, PCONTEXT _context)
{
	Inst instruction;
	GetOneInst(_address, &instruction);

	//return instruction
	if(IsInstRet(_address))
		_destAddress[0] = *((ADDRESS *)_context->Esp);
	else
	{
		if(GetModFromModrm(instruction.modrm) == 0)
		{
			if(GetRmFromModrm(instruction.modrm) == 5)
			{
				int *destAddressPointer;
				destAddressPointer = (int *)instruction.disp;
				*_destAddress = *destAddressPointer;
			}
			else if(GetRmFromModrm(instruction.modrm) == 4)
			{
				//SIB  00 100 SIB 
				if(GetRmFromModrm(instruction.sib) == 5)
				{
					int exponent = GetModFromModrm(instruction.sib);
					int multiplier = (int)(pow(2, exponent));
					signed int reg = GetRegValue(GetRegFromModrm(instruction.sib), _context);
					*_destAddress = *(ADDRESS *)(instruction.disp + multiplier * reg);
				}
				else
				{
					PrintInst(_address, T_ERROR);
					RLBinUtils::RLBin_Error("Unhandled Inditect CTI, Haven't seen this type of instruction before!", __FILENAME__, __LINE__);
				}
				//END SIB
			}
			else
			{
				int regvalue = GetRegValue(GetRmFromModrm(instruction.modrm), _context);
				*_destAddress = *(ADDRESS *)regvalue;
			}
		}
		else if(GetModFromModrm(instruction.modrm) == 3)
		{
			int regvalue = GetRegValue(GetRmFromModrm(instruction.modrm), _context);
			*_destAddress = regvalue;
		}
		else if(GetModFromModrm(instruction.modrm) == 1)
		{
			if(GetRmFromModrm(instruction.modrm) == 4)
			{
				//SIB  01 100 SIB  +  disp8  Mode
				if((GetRegFromModrm(instruction.sib) == 4)&&(GetRmFromModrm(instruction.sib) == 4)) // Illegal, just for esp
				{
					//esp_flagged.insert(esp_flagged.begin(), _address);
					signed char disp8 = instruction.bytes[3];
					int regvalue = _context->Esp + int(disp8);
					printf("%s \t %s \t %08x \t  %d \n", instruction.mnemonic, instruction.op_str, *(ADDRESS *)regvalue, disp8);
					*_destAddress = *(ADDRESS *)regvalue;	
				}	
				else
				{	
					PrintInst(_address, T_ERROR);
					RLBinUtils::RLBin_Error("Unhandled Inditect CTI, Haven't seen this type of instruction before!", __FILENAME__, __LINE__);
				}
				//ENDSIB
			}
			else
			{
				int regvalue = GetRegValue(GetRmFromModrm(instruction.modrm), _context); 
				signed char disp8 = instruction.bytes[2];
				regvalue = regvalue + int(disp8);
				*_destAddress = *(ADDRESS *)regvalue;
			}
		}
		else if(GetModFromModrm(instruction.modrm) == 2)
		{
			if(GetRmFromModrm(instruction.modrm) == 4)
			{
				//SIB  10 100 SIB  +  disp32  Mode
				//ENDSIB
				PrintInst(_address, T_ERROR);
				RLBinUtils::RLBin_Error("Unhandled Inditect CTI, Haven't seen this type of instruction before!", __FILENAME__, __LINE__);
			}
			else
			{
				int regvalue = GetRegValue(GetRmFromModrm(instruction.modrm), _context); 
				signed int disp32 = instruction.disp;
				regvalue = regvalue + disp32;
				*_destAddress = *(ADDRESS *)regvalue;
			}
		}
		else
		{
			PrintInst(_address, T_ERROR);
			RLBinUtils::RLBin_Error("Unhandled Inditect CTI, Haven't seen this type of instruction before!", __FILENAME__, __LINE__);
		}
	}

	// check if destination is a library call, if so add it to the unordered map
	std::string lib_name = Modules::Get()->GetExpFuncName(* _destAddress);
	if(lib_name != "")
	{
		libcalls[_address] = lib_name;
	}
}
