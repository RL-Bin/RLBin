/**
 * @file Disassembler.cpp
 * @brief Defines the body of functions in Disassembler class.
 */

#include "..\..\include\SubUnits\Disassembler\Disassembler.h"

// inititalizing the only instace of class 
Disassembler* Disassembler::s_instance = NULL;

Disassembler* Disassembler::Create(void) 
{
	if (s_instance != NULL)
	{
		RLBinUtils::RLBin_Error("An instance of Disassembler exists", __FILENAME__, __LINE__);
		return NULL;
	}
	s_instance = new Disassembler();
	return s_instance;
}

Disassembler* Disassembler::Get(void) 
{
	if (s_instance == NULL)
	{
		RLBinUtils::RLBin_Error("Disassembler is not initialized yet!", __FILENAME__, __LINE__);
		return NULL;
	}
	return s_instance;
}

void Disassembler::Initialize(void) 
{

}
