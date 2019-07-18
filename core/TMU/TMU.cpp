/**
 * @file TMU.cpp
 * @brief Defines the body of functions in TMU class.
 */

#include "..\include\TMU\TMU.h"

#include "..\include\SubUnits\Modules\Modules.h"

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
	InsertTrampoine(add);
}

void TMU::InsertTrampoine(ADDRESS _address)
{
	RLBinUtils::SetWritePermission(_address, 1);

	byte orig_code = *(byte *) _address;

	*(byte *) _address = TRAP_INST_OPCODE;	

	original_code.insert({_address, orig_code});
}

void TMU::RemoveTrampoine(ADDRESS _address)
{
	*(byte *) _address = original_code.at(_address);

	original_code.erase(_address);
}