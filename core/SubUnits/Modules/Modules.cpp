/**
 * @file Modules.cpp
 * @brief Defines the body of functions in Modules class.
 */

#include "..\..\include\SubUnits\Modules\Modules.h"

// inititalizing the only instace of class 
Modules* Modules::s_instance = NULL;

Modules* Modules::Create(void) 
{
	if (s_instance != NULL)
	{
		RLBinUtils::RLBin_Error("An instance of Modules exists", __FILENAME__, __LINE__);
		return NULL;
	}
	s_instance = new Modules();
	return s_instance;
}

Modules* Modules::Get(void) 
{
	if (s_instance == NULL)
	{
		RLBinUtils::RLBin_Error("Modules is not initialized yet!", __FILENAME__, __LINE__);
		return NULL;
	}
	return s_instance;
}

void Modules::Initialize(void) 
{

}
