/**
 * @file Funcs.cpp
 * @brief Defines the body of functions in Funcs class.
 */

#include "..\..\include\DataStructs\Funcs\Funcs.h"

// inititalizing the only instace of class 
Funcs* Funcs::s_instance = NULL;

Funcs* Funcs::Create(void) 
{
	if (s_instance != NULL)
	{
		RLBinUtils::RLBin_Error("An instance of Funcs exists", __FILENAME__, __LINE__);
		return NULL;
	}
	s_instance = new Funcs();
	return s_instance;
}

Funcs* Funcs::Get(void) 
{
	if (s_instance == NULL)
	{
		RLBinUtils::RLBin_Error("Funcs is not initialized yet!", __FILENAME__, __LINE__);
		return NULL;
	}
	return s_instance;
}

void Funcs::Initialize(void) 
{

}
