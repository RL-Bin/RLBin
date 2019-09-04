/**
 * @file TMU.cpp
 * @brief Defines the body of functions in TMU class.
 */

#include "..\include\TMU\TMU.h"

#include "..\include\SubUnits\Modules\Modules.h"
#include "..\include\SubUnits\Disassembler\Disassembler.h"

// inititalizing the only instace of class 
TMU* TMU::s_instance = NULL;

TMU* TMU::Create(void) 
{
	if (s_instance != NULL)
	{
		RLBinUtils::RLBin_Error("An instance of TMU exists", __FILENAME__, __LINE__);
		return NULL;
	}
	s_instance = new TMU();
	return s_instance;
}

TMU* TMU::Get(void) 
{
	if (s_instance == NULL)
	{
		RLBinUtils::RLBin_Error("TMU is not initialized yet!", __FILENAME__, __LINE__);
		return NULL;
	}
	return s_instance;
}

void TMU::Initialize(void) 
{
	ADDRESS add = Modules::Get()->GetMainModule()->entry_point;
	InsertTrampoline(add);
}

void TMU::InsertTrampoline(ADDRESS _address)
{
	// Debug, check the list of trampolines
	//ListTrampolines();

	// First, check if current location has trampoline
	if(tramps_cc.find(_address) != tramps_cc.end())
	{
		RLBinUtils::RLBin_Tram("Trampoline already exist at location " + RLBinUtils::ConvertHexToString(_address));
		return;
	}

	RLBinUtils::RLBin_Tram(RLBinUtils::ConvertHexToString(_address));

	// Fill out the trampoline class
	byte original_code = *(byte *)_address;
	tramps_cc.insert({_address, original_code});

	// Write the trampoline to memory
	RLBinUtils::SetWritePermission(_address, 1);
	*(byte *) _address = TRAP_INST_OPCODE;	

	return;
}

void TMU::InsertCheckTrampoline(ADDRESS _address, ADDRESS _routine, PEXCEPTION_POINTERS p)
{
	if(*(byte *)_address == 0xC3)
	{
		InsertTrampoline(_address);
	}

	else if(*(byte *)_address == 0xC2)
	{
		InsertTrampoline(_address);
	}

	else if((*(byte *)_address == 0xFF) && (*((byte *)_address+1) == 0x15))
	{
		*(byte *) _address = 0x90;
		*((byte *) _address + 1) = 0xE8;
		*(ADDRESS *) ((byte *) _address + 2) = _routine - _address -6;
		Disassembler::Get()->PrintInst(*(ADDRESS *)((byte *) _address + 1), T_DEBUG);
	}

	else if((*(byte *)_address == 0xFF) && ((*((byte *)_address+1)&0xF0) == 0xD0))
	{
		InsertTrampoline(_address);		
	}

	return;
}

void TMU::RemoveTrampoline(ADDRESS _address)
{
	*(byte *) _address = tramps_cc[_address];

	//Trampoline * tr = tramps_cc[_address];
	
	//delete tr;

	//tr->~Trampoline();

	tramps_cc.erase(_address);
}

void TMU::ListTrampolines()
{
	std::unordered_map<ADDRESS,byte>::iterator it = tramps_cc.begin();

	while(it != tramps_cc.end())
	{
		RLBinUtils::RLBin_Tram(RLBinUtils::ConvertHexToString(it->first) );// + " " + RLBinUtils::ConvertHexToString((ADDRESS)(it->second)));
		it ++;
	}
	RLBinUtils::RLBin_Tram("___________________________");
}

void TMU::RemoveAllTrampolines()
{
	ListTrampolines();
	while(tramps_cc.size() != 0)
	{
		std::unordered_map<ADDRESS, byte>::iterator it = tramps_cc.begin();
		RemoveTrampoline(it->first);
	}	
}
