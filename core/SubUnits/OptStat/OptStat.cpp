/**
 * @file OptStat.cpp
 * @brief Defines the body of functions in OptStat class.
 */

#include "..\..\include\SubUnits\OptStat\OptStat.h"

// inititalizing the only instace of class 
OptStat* OptStat::s_instance = NULL;

OptStat* OptStat::Create(void) 
{
	if (s_instance != NULL)
	{
		RLBinUtils::RLBin_Error("An instance of OptStat exists", __FILENAME__, __LINE__);
		return NULL;
	}
	s_instance = new OptStat();
	return s_instance;
}

OptStat* OptStat::Get(void) 
{
	if (s_instance == NULL)
	{
		RLBinUtils::RLBin_Error("OptStat is not initialized yet!", __FILENAME__, __LINE__);
		return NULL;
	}
	return s_instance;
}

void OptStat::Initialize(void) 
{

}
