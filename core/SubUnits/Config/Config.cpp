/**
 * @file Config.cpp
 * @brief Defines the body of functions in Config class.
 */

#include "..\..\include\SubUnits\Config\Config.h"

// inititalizing the only instace of class 
Config* Config::s_instance = NULL;

Config* Config::Create(void) 
{
	if (s_instance != NULL)
	{
		RLBinUtils::RLBin_Error("An instance of Config exists", __FILENAME__, __LINE__);
		return NULL;
	}
	s_instance = new Config();
	return s_instance;
}

Config* Config::Get(void) 
{
	if (s_instance == NULL)
	{
		RLBinUtils::RLBin_Error("Config is not initialized yet!", __FILENAME__, __LINE__);
		return NULL;
	}
	return s_instance;
}

void Config::Initialize(void) 
{

}
