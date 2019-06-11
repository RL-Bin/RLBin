/**
 * @file CU.cpp
 * @brief Defines the body of functions in CU class.
 */

#include "..\include\CU\CU.h"

/** inititalizing the only instace of class */
CU* CU::s_instance = NULL;

CU* CU::Create(void) 
{
	if (s_instance != NULL)
	{
		RLBinUtils::RLBin_Error("An instance of CU exists", __FILENAME__, __LINE__);
		return NULL;
	}
	s_instance = new CU();
	return s_instance;
}

CU* CU::Get(void) 
{
	if (s_instance == NULL)
	{
		RLBinUtils::RLBin_Error("CU is not initialized yet!", __FILENAME__, __LINE__);
		return NULL;
	}
	return s_instance;
}