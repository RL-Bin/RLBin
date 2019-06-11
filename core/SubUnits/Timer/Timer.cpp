/**
 * @file Timer.cpp
 * @brief Defines the body of functions in Timer class.
 */

#include "..\..\include\SubUnits\Timer\Timer.h"

// inititalizing the only instace of class 
Timer* Timer::s_instance = NULL;

Timer* Timer::Create(void) 
{
	if (s_instance != NULL)
	{
		RLBinUtils::RLBin_Error("An instance of Timer exists", __FILENAME__, __LINE__);
		return NULL;
	}
	s_instance = new Timer();
	return s_instance;
}

Timer* Timer::Get(void) 
{
	if (s_instance == NULL)
	{
		RLBinUtils::RLBin_Error("Timer is not initialized yet!", __FILENAME__, __LINE__);
		return NULL;
	}
	return s_instance;
}

void Timer::Initialize(void) 
{

}
