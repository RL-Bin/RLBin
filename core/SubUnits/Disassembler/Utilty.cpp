/**
 * @file Utilty.cpp
 * @brief Implementation of the utility functions in Disassembler class    
 */

#include "..\..\include\SubUnits\Disassembler\Disassembler.h"

bool Disassembler::GetOneInst(int address, Inst *instruction)
{
	unsigned char code[15] = { 0 };
	ReadProcessMemory(GetCurrentProcess(), (LPCVOID)address, code, sizeof(code), 0);
	cs_insn *insn;
	csh handle;
	size_t count;
	if (cs_open(CS_ARCH_X86, CS_MODE_32, &handle)) 
	{
		RLBinUtils::RLBin_Error("ERROR: Failed to initialize Capstone Disassembly Engine!\n", __FILENAME__, __LINE__);
		return false;
	}
	cs_option(handle, CS_OPT_DETAIL, CS_OPT_ON);
	count = cs_disasm(handle, code, sizeof(code) - 1, address, 1, &insn);
	if (count) 
	{
		instruction->GetFromCapstone(insn[0].id, (ADDRESS)insn[0].address, insn[0].size, insn[0].bytes, insn[0].mnemonic, insn[0].op_str, 
			insn[0].detail->x86.prefix, insn[0].detail->x86.opcode, insn[0].detail->x86.addr_size, insn[0].detail->x86.modrm, insn[0].detail->x86.sib,
			insn[0].detail->x86.disp, insn[0].detail->x86.sib_index, insn[0].detail->x86.sib_scale, insn[0].detail->x86.sib_base, 
			insn[0].detail->x86.op_count, insn[0].detail->x86.operands);
		cs_free(insn, count);
	}
	else
	{
		RLBinUtils::RLBin_Error("ERROR: Failed to disassemble given code at address " + RLBinUtils::ConvertHexToString(address) + "\n", __FILENAME__, __LINE__);
		return false;
	}
	cs_close(&handle);
	return true;
}

bool Disassembler::IsValidInst(int address)
{
	unsigned char code[15] = { 0 };
	ReadProcessMemory(GetCurrentProcess(), (LPCVOID)address, code, sizeof(code), 0);
	cs_insn *insn;
	csh handle;
	size_t count;
	if (cs_open(CS_ARCH_X86, CS_MODE_32, &handle)) 
	{
		RLBinUtils::RLBin_Error("ERROR: Failed to initialize Capstone Disassembly Engine!\n", __FILENAME__, __LINE__);
		return false;
	}
	cs_option(handle, CS_OPT_DETAIL, CS_OPT_ON);
	count = cs_disasm(handle, code, sizeof(code) - 1, address, 1, &insn);
	cs_free(insn, count);
	cs_close(&handle);
	if (count)
	{
		return true;				
	}
	else
		return false;
}

int Disassembler::GetInstSize(ADDRESS address)
{
	Inst inst;
	GetOneInst(address, &inst);
	return inst.size;
}

void Disassembler::PrintInst(ADDRESS _address, LogType _log_type)
{
	Inst inst;
	GetOneInst(_address, &inst);
	RLBinUtils::RLBin_Multi((RLBinUtils::ConvertHexToString((int)inst.address) + 
				std::string(":\t ") + inst.mnemonic + std::string(" ") + inst.op_str), _log_type);
	return;
}

void Disassembler::PrintInstDetails(ADDRESS _address, LogType _log_type)
{
	Inst inst;
	GetOneInst(_address, &inst);
	Inst *pinstruction = &inst;
	RLBinUtils::RLBin_Multi(("\n-------------------------------------------------------------\n"),_log_type);
	RLBinUtils::RLBin_Multi((("address: \t ") + RLBinUtils::ConvertHexToString(pinstruction->address)),_log_type);
	RLBinUtils::RLBin_Multi((("mnemonic: \t ") + RLBinUtils::ConvertCharPtrToString(pinstruction->mnemonic)),_log_type);
	RLBinUtils::RLBin_Multi((("op_str: \t ") + RLBinUtils::ConvertCharPtrToString(pinstruction->op_str)),_log_type);
	RLBinUtils::RLBin_Multi((("size \t ") + RLBinUtils::ConvertIntToString(pinstruction->size)),_log_type);
	RLBinUtils::RLBin_Multi(("bytes: \t"),_log_type);
	for (int i = 0; i < pinstruction->size; i++)
	{
		RLBinUtils::RLBin_Multi((RLBinUtils::ConvertByteToString(pinstruction->bytes[i])),_log_type);
	}
	RLBinUtils::RLBin_Multi((("id \t ") + RLBinUtils::ConvertIntToString(pinstruction->id)),_log_type);
	RLBinUtils::RLBin_Multi(("---------------Details-------------\n"),_log_type);
	RLBinUtils::RLBin_Multi((("displacement: \t ") + RLBinUtils::ConvertHexToString(pinstruction->disp) + std::string("\n")),_log_type);
	return;	
}


void Disassembler::PrintDisassembly()
{
	// go over all entries in the table and print out the discovered insructions  
	SIZE_TYPE covered_bytes = 0;
	SIZE_TYPE covered_instructions = 0;
	ADDRESS start = Modules::Get()->GetMainModule()->base_address;
	ADDRESS end = Modules::Get()->GetMainModule()->base_address + Modules::Get()->GetMainModule()-> module_size;
	for (ADDRESS i = start; i < end;)
	{
		if (DisTable::Get()->GetEntry(i) != LOC_UNDISCOVERD)
		{
			Inst inst;
			GetOneInst(i, &inst);
       		std::string tempStr;			
			tempStr.append(RLBinUtils::ConvertHexToString(i) + "\t" + RLBinUtils::ConvertIntToString(DisTable::Get()->GetEntry(i))  + "\t " + inst.mnemonic + " " + inst.op_str );

       		tempStr.resize(60, ' ');
       		tempStr.append("0x");
			for (int i = 0; i < inst.size; i++)
			{
				tempStr.append(RLBinUtils::ConvertByteToString(inst.bytes[i]));
			}

       		tempStr.resize(90, ' ');

			if(libcalls.find(i) != libcalls.end())
			{
				tempStr.append(" " + libcalls[i] + " ");
			}       		

        	tempStr.append("\n");       			
			RLBinUtils::RLBin_Dis(tempStr);
			i = i+inst.size;
			covered_bytes = covered_bytes + inst.size;
			covered_instructions ++;
		}
		else
			i++;
	}
	RLBinUtils::RLBin_Dis("\n____________________________TOTAL_SIZE_____________________________\n");
	RLBinUtils::RLBin_Dis("Total Bytes Discovered dynamically\t" + RLBinUtils::ConvertIntToString(covered_bytes) + " bytes\n");
	RLBinUtils::RLBin_Dis("Total Instructions Discovered dynamically\t" + RLBinUtils::ConvertIntToString(covered_instructions));
}

void Disassembler::PrintNInsts(ADDRESS _address, LogType _log_type, int _size)
{
	ADDRESS printed_address = _address;
	while(_size>0)
	{
		Inst inst;
		GetOneInst(printed_address, &inst);
		RLBinUtils::RLBin_Multi((RLBinUtils::ConvertHexToString((int)inst.address) + 
					std::string(":\t ") + inst.mnemonic + std::string(" ") + inst.op_str), _log_type);
		_size--;
		printed_address += inst.size;
	}
	return;
}