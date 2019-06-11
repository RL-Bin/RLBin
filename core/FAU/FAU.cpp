/**
 * @file FAU.cpp
 * @brief Defines the body of functions in FAU class.
 */

#include "..\include\FAU\FAU.h"

// inititalizing the only instace of class 
FAU* FAU::s_instance = NULL;

FAU* FAU::Create(void) 
{
	if (s_instance != NULL)
	{
		RLBinUtils::RLBin_Error("An instance of FAU exists", __FILENAME__, __LINE__);
		return NULL;
	}
	s_instance = new FAU();
	return s_instance;
}

FAU* FAU::Get(void) 
{
	if (s_instance == NULL)
	{
		RLBinUtils::RLBin_Error("FAU is not initialized yet!", __FILENAME__, __LINE__);
		return NULL;
	}
	return s_instance;
}

void FAU::Initialize(void) 
{

}
