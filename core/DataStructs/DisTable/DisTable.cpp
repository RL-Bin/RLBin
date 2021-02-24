/**
 * @file DisTable.cpp
 * @brief Defines the body of functions in DisTable class.
 */

#include "..\..\include\DataStructs\DisTable\DisTable.h"

#include "..\..\include\SubUnits\Modules\Modules.h"

// inititalizing the only instace of class 
DisTable* DisTable::s_instance = NULL;

DisTable* DisTable::Create(void) 
{
	if (s_instance != NULL)
	{
		RLBinUtils::RLBin_Error("An instance of DisTable exists", __FILENAME__, __LINE__);
		return NULL;
	}
	s_instance = new DisTable();
	return s_instance;
}

DisTable* DisTable::Get(void) 
{
	if (s_instance == NULL)
	{
		RLBinUtils::RLBin_Error("DisTable is not initialized yet!", __FILENAME__, __LINE__);
		return NULL;
	}
	return s_instance;
}

void DisTable::Initialize(SIZE_TYPE _size)
{
	// allocate memory and set all entries to unsicovered
	size = _size;
	table = new CELL[_size];
	if(table == NULL)
	{
		RLBinUtils::RLBin_Error("DisTable:: cannot allocate the memory!", __FILENAME__, __LINE__);
	}
	RLBinUtils::RLBin_Log("DisTable DataStruct Created! with size " + RLBinUtils::ConvertHexToString(_size), __FILENAME__);

	for (int i = 0; i < _size; i++)
	{
		table[i] = LOC_UNDISCOVERD;
	}

	offset = ADDRESS (table) - Modules::Get()->GetMainModule()->base_address;
}

DisTable::~DisTable()
{
	// Delete the memory initiated for the table
	delete [] table;
	table = NULL;
}

void DisTable::SetEntry(ADDRESS _address, CELL _value)
{
	// if the address is in the range of this module, sets the table entry
	if(Modules::Get()->IsInsideMainModule(_address))
	{
		table[_address - Modules::Get()->GetMainModule()->base_address] = _value;
	}
	else
	{
		RLBinUtils::RLBin_Error("Trying to set disassembly table for an invalid address" + RLBinUtils::ConvertHexToString(_address) + "\n", __FILENAME__, __LINE__);
	}
}		

CELL DisTable::GetEntry(ADDRESS _address)
{
	// if the address is in the range of this module, return the table entry 
	if(Modules::Get()->IsInsideMainModule(_address))
	{
		return table[_address - Modules::Get()->GetMainModule()->base_address];
	}
	else
	{
		RLBinUtils::RLBin_Error("Trying to get disassembly table for an invalid address" + RLBinUtils::ConvertHexToString(_address) + "\n", __FILENAME__, __LINE__);
		return LOC_UNDISCOVERD;
	}
}

ADDRESS DisTable::GetOffset()
{
	return offset;
}
