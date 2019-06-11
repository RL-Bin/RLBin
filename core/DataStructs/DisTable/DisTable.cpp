/**
 * @file DisTable.cpp
 * @brief Defines the body of functions in DisTable class.
 */

#include "..\..\include\DataStructs\DisTable\DisTable.h"

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

void DisTable::Initialize(void) 
{

}
