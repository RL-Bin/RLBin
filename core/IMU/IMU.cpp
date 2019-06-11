/**
 * @file IMU.cpp
 * @brief Defines the body of functions in IMU class.
 */

#include "..\include\IMU\IMU.h"

// inititalizing the only instace of class 
IMU* IMU::s_instance = NULL;

IMU* IMU::Create(void) 
{
	if (s_instance != NULL)
	{
		RLBinUtils::RLBin_Error("An instance of IMU exists", __FILENAME__, __LINE__);
		return NULL;
	}
	s_instance = new IMU();
	return s_instance;
}

IMU* IMU::Get(void) 
{
	if (s_instance == NULL)
	{
		RLBinUtils::RLBin_Error("IMU is not initialized yet!", __FILENAME__, __LINE__);
		return NULL;
	}
	return s_instance;
}

void IMU::Initialize(void) 
{

}
