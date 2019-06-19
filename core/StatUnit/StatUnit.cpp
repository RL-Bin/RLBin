/**
 * @file StatUnit.cpp
 * @brief Defines the body of functions in StatUnit class.
 */

#include "..\include\StatUnit\StatUnit.h"

#include "..\include\SubUnits\Modules\Modules.h"


// inititalizing the only instace of class 
StatUnit* StatUnit::s_instance = NULL;

StatUnit* StatUnit::Create(void) 
{
	if (s_instance != NULL)
	{
		RLBinUtils::RLBin_Error("An instance of StatUnit exists", __FILENAME__, __LINE__);
		return NULL;
	}
	RLBinUtils::RLBin_Log("StatUnit Created!", __FILENAME__);
	s_instance = new StatUnit();
	return s_instance;
}

StatUnit* StatUnit::Get(void) 
{
	if (s_instance == NULL)
	{
		RLBinUtils::RLBin_Error("StatUnit is not initialized yet!", __FILENAME__, __LINE__);
		return NULL;
	}
	return s_instance;
}

void StatUnit::Run() 
{
	Modules::Create();
	Modules::Get()->Initialize();
}

void StatUnit::Disassemble() 
{

}
