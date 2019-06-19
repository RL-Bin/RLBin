/**
 * @file Config.cpp
 * @brief Defines the body of functions in Config class.
 */

#include <map>
#include <string>
#include <fstream>
#include <iostream>

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
	RLBinUtils::RLBin_Log("Reading configuration file.", __FILENAME__);
    std::ifstream config_stream(CURRENT_CONFIG_FILE);
	if(!config_stream)
	{
		RLBinUtils::RLBin_Log("Config file not found! Will continue with the default configuration.", __FILENAME__);
		conf["OptMode"] = 1;
		conf["OptLevel"] = 1;
		conf["DisLog"] = 0;
		conf["ModLog"] = 0;
		conf["OptLog"] = 0;
		conf["ThreadLog"] = 0;
		conf["TimeLog"] = 0;
		conf["TrampLog"] = 0;
		return;
	}
	RLBinUtils::RLBin_Log("Configuration information retrieved from the file.", __FILENAME__);
	std::string line;
	while( std::getline(config_stream, line) )
	{
		//ignore empty line
		if(line == "") continue;

		//ignore comments
		if (line.rfind("//", 0) == 0) continue;

		std::string delimiter = "=";
		std::string key = line.substr(0, line.find(delimiter));
		std::string value = line.substr(line.find(delimiter)+1, line.size());
		conf[key] = std::stoi(value);
	}
	return;
}

void Config::PrintConfigs()
{
	std::map<std::string, int>::iterator it;
	for (it = conf.begin(); it != conf.end(); it++)
	{
	    std::cout << it->first    // string (key)
	              << ':'
	              << it->second   // string's value 
	              << std::endl ;
	}
	return;
}

int Config::GetFeatureValue(std::string feature)
{
	if(conf.find(feature) == conf.end()) 
	{
		RLBinUtils::RLBin_Error("This configuration cannot be found in the config file!    :    " + feature, __FILENAME__, __LINE__);
		return 0;
	} 
	else 
	{
		return conf[feature];
	}
}