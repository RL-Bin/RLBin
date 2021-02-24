/**
 * @file Opcode.cpp
 * @brief Implements some of the functions in Disassembler class that disect the instructions    
 */

#include "..\..\include\SubUnits\Disassembler\Disassembler.h"

bool Disassembler::IsInstRet(ADDRESS _address)
{
	Inst instruction;
	GetOneInst(_address, &instruction);
	//	opcode 		Inst 			operand			flag			size
	//+	0xC2		ret (near)		imm16			none			3
	//+	0xC3		ret (near)		none			none			1
	//+	0xCA		ret (far)		imm16			none			3
	//+	0xCB		ret (far)		none			none			1
	if((instruction.opcode[0] == 0xCA)||(instruction.opcode[0] == 0xCB))
	{
		//RLBinUtils::RLBin_Error(RLBinUtils::ConvertHexToString(_address) + "\tInstruction not supproted yet!\t" +
		//	RLBinUtils::ConvertCharPtrToString(instruction.mnemonic) + "\t" + RLBinUtils::ConvertByteToString(instruction.opcode[0]), __FILENAME__, __LINE__);
		return true;
	}
	else if((instruction.opcode[0] == 0xC3)||(instruction.opcode[0] == 0xC2))
	{
		//RLBinUtils::RLBin_TimeStat(RLBinUtils::ConvertHexToString(_address) + "\tInstruction Check!\t" +
		//	RLBinUtils::ConvertCharPtrToString(instruction.mnemonic) + "\t" + RLBinUtils::ConvertByteToString(instruction.opcode[0]));
		return true;
	} 
	return false;
}

bool Disassembler::IsInstUnconditionalJump(ADDRESS _address)
{
	Inst instruction;
	GetOneInst(_address, &instruction);
	//	opcode 		Inst 			operand			flag			size
	//+	0xEB		JMP 			rel8			none			1
	//+	0xE9		JMP 			rel32			none			5
	//-	0xEA		JMPF 			N/A 			N/A				N/A
	if(instruction.opcode[0] == 0xEA)
	{
		PrintInst(_address, T_ERROR);		
		
		RLBinUtils::RLBin_Error(RLBinUtils::ConvertHexToString(_address) + "\tInstruction not supproted yet!\t" +
			RLBinUtils::ConvertCharPtrToString(instruction.mnemonic) + "\t" + RLBinUtils::ConvertByteToString(instruction.opcode[0]), __FILENAME__, __LINE__);
		return true;
	}
	else if((instruction.opcode[0] == 0xEB) || (instruction.opcode[0] == 0xE9))
	{
		return true;
	} 
	return false;
}

bool Disassembler::IsInstDirectJump(ADDRESS _address)
{
	if (IsInstUnconditionalJump(_address) || IsInstConditionalJump(_address))
	{
		return true;
	}
	return false;
}

bool Disassembler::IsInstDirectCall(ADDRESS _address)
{
	Inst instruction;
	GetOneInst(_address, &instruction);
	//	opcode 		Inst 			operand			flag			size
	//+	0xE8		CALL 			rel32			none			5
	//-	0x9A		CALLF 			far direct 		none			7
	if(instruction.opcode[0] == 0x9A)
	{
		RLBinUtils::RLBin_Error(RLBinUtils::ConvertHexToString(_address) + "\tInstruction not supproted yet!\t" +
			RLBinUtils::ConvertCharPtrToString(instruction.mnemonic) + "\t" + RLBinUtils::ConvertByteToString(instruction.opcode[0]), __FILENAME__, __LINE__);
		return true;
	}
	else if((instruction.opcode[0] == 0xE8))
	{
		return true;
	} 
	return false;
}


bool Disassembler::IsInstConditionalJump(ADDRESS _address)
{
	Inst instruction;
	GetOneInst(_address, &instruction);
	//	opcode 			Inst 			operand			flag			size
	//+	0x70 			JO 				rel8			none			3,7+
	//+	0x71 			JNO 			rel8			none			3,7+
	//+	0x72 			JB 				rel8			none			3,7+
	//+	0x73 			JNB 			rel8			none			3,7+
	//+	0x74 			JZ 				rel8			none			3,7+
	//+	0x75 			JNZ 			rel8			none			3,7+
	//+	0x76 			JBE 			rel8			none			3,7+
	//+	0x77 			JNBE 			rel8			none			3,7+
	//+	0x78 			JS 				rel8			none			3,7+
	//+	0x79 			JNS 			rel8			none			3,7+
	//+	0x7A 			JP 				rel8			none			3,7+
	//+	0x7B 			JNP 			rel8			none			3,7+
	//+	0x7C 			JL 				rel8			none			3,7+
	//+	0x7D 			JNL 			rel8			none			3,7+
	//+	0x7E 			JLE 			rel8			none			3,7+
	//+	0x7F 			JNLE 			rel8			none			3,7+
	//+	0x0F 80 		JO 				rel32			none			3,7+
	//+	0x0F 81 		JNO 			rel32			none			3,7+
	//+	0x0F 82 		JB 				rel32			none			3,7+
	//+	0x0F 83 		JNB 			rel32			none			3,7+
	//+	0x0F 84 		JZ 				rel32			none			3,7+
	//+	0x0F 85 		JNZ 			rel32			none			3,7+
	//+	0x0F 86 		JBE 			rel32			none			3,7+
	//+	0x0F 87 		JNBE 			rel32			none			3,7+
	//+	0x0F 88 		JS 				rel32			none			3,7+
	//+	0x0F 89 		JNS 			rel32			none			3,7+
	//+	0x0F 8A 		JP 				rel32			none			3,7+
	//+	0x0F 8B 		JNP 			rel32			none			3,7+
	//+	0x0F 8C 		JL 				rel32			none			3,7+
	//+	0x0F 8D 		JNL 			rel32			none			3,7+
	//+	0x0F 8E 		JLE 			rel32			none			3,7+
	//+	0x0F 8F 		JNLE 			rel32			none			3,7+
	//+	0xE0  			LOOPNZ 			rel8			none			11+
	//+	0xE1  			LOOPZ 			rel8			none			11+
	//+	0xE2  			LOOP 			rel8			none			11+
	//+	0xE3  			JECXZ 			rel8			none			N/A
	if((instruction.opcode[0] >= 0xE0) && (instruction.opcode[0] <= 0xE3))
	{
		return true;
	}
	else if((instruction.opcode[0] == 0x0F) && (instruction.opcode[1] <= 0x8F) && (instruction.opcode[1] >= 0x80))
	{
		return true;
	}
	else if((instruction.opcode[0] <= 0x7F) && (instruction.opcode[0] >= 0x70))
	{
		return true;
	} 
	return false;
}

bool Disassembler::IsInstIndirectJump(ADDRESS _address)
{
	Inst instruction;
	GetOneInst(_address, &instruction);
	//	opcode 		Inst 			operand			flag			size
	//+	0xFF /4		JMP 			reg/mem			none			2+
	//-	0xFF /5		JMPF 			reg/mem			none			2+	
	if((instruction.opcode[0] == 0xFF)&&(GetRegFromModrm(instruction.modrm) == 0x05))
	{
		RLBinUtils::RLBin_Error(RLBinUtils::ConvertHexToString(_address) + "\tInstruction not supproted yet!\t" +
			RLBinUtils::ConvertCharPtrToString(instruction.mnemonic) + "\t" + RLBinUtils::ConvertByteToString(instruction.opcode[0]), __FILENAME__, __LINE__);
		return true;
	}
	else if((instruction.opcode[0] == 0xFF)&&(GetRegFromModrm(instruction.modrm) == 0x04))
	{
		return true;
	} 
	return false;
}


bool Disassembler::IsInstIndirectCall(ADDRESS _address)
{
	Inst instruction;
	GetOneInst(_address, &instruction);
	//	opcode 		Inst 			operand			flag			size
	//+	0xFF /2		CALL 			reg/mem			none			2+
	//-	0xFF /3		CALLF 			reg/mem			none			2+	
	if((instruction.opcode[0] == 0xFF)&&(GetRegFromModrm(instruction.modrm) == 0x03))
	{
		RLBinUtils::RLBin_Error(RLBinUtils::ConvertHexToString(_address) + "\tInstruction not supproted yet!\t" +
			RLBinUtils::ConvertCharPtrToString(instruction.mnemonic) + "\t" + RLBinUtils::ConvertByteToString(instruction.opcode[0]), __FILENAME__, __LINE__);
		return true;
	}
	else if((instruction.opcode[0] == 0xFF)&&(GetRegFromModrm(instruction.modrm) == 0x02))
	{
		return true;
	} 
	return false;
}


bool Disassembler::IsInstDirectCTI(ADDRESS _address)
{
	if (IsInstDirectJump(_address) || IsInstDirectCall(_address))
	{
		return true;
	}
	return false;
}

bool Disassembler::IsInstIndirectCTI(ADDRESS _address)
{
	if (IsInstRet(_address)) 
	{
		return true;
	}
	else if (IsInstIndirectJump(_address) || IsInstIndirectCall(_address))
	{
			return true;
	}
	return false;
}

int Disassembler::GetRegValue(int _num, PCONTEXT _context)
{
	if(_num == 0)
		return _context->Eax; 
	if(_num == 1)
		return _context->Ecx; 
	if(_num == 2)
		return _context->Edx; 
	if(_num == 3)
		return _context->Ebx; 
	if(_num == 4)
		return _context->Esp; 
	if(_num == 5)
		return _context->Ebp;
	if(_num == 6)
		return _context->Esi; 
	if(_num == 7)
		return _context->Edi;
	RLBinUtils::RLBin_Error("Invalid register requestd" + RLBinUtils::ConvertIntToString(_num), __FILENAME__, __LINE__);
	return 0;
}

uint8_t Disassembler::GetRegFromModrm(uint8_t _modrm)
{
	uint8_t reg = ((_modrm & 0x38) >> 3);
	return reg;
}

uint8_t Disassembler::GetModFromModrm(uint8_t _modrm)
{
	uint8_t mod = ((_modrm & 0xC0) >> 6);
	return mod;
}

uint8_t Disassembler::GetRmFromModrm(uint8_t _modrm)
{
	uint8_t rm = (_modrm & 0x07);
	return rm;
}