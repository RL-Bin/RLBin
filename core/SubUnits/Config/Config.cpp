/**
 * @file Config.cpp
 * @brief Defines the body of functions in Config class.
 */

#include <map>
#include <string>
#include <fstream>
#include <iostream>

#include "..\..\include\SubUnits\Config\Config.h"
#include "..\..\include\CLI11\CLI11.hpp"

int Config::mode = 0;
int Config::optlevel = 0;
int Config::verbosity = 0;
bool Config::code_pointer = false;

void Config::Initialize(void) 
{
	RLBinUtils::RLBin_Log("Reading configuration file.", __FILENAME__);
 
 	std::ifstream config_stream(CURRENT_CONFIG_FILE);
	if(!config_stream){
		RLBinUtils::RLBin_Log("Config file not found! Will continue with the default configuration.", __FILENAME__);
		return;
	}
	std::string line;
	std::getline(config_stream, line);
	
	if(line == "native")
		mode = 0;		
	else if(line == "static")
		mode = 1;
	else if(line == "dynamic")
		mode = 2;
	else
		mode = 3;

	if(mode>1){
		std::getline(config_stream, line);
		optlevel = RLBinUtils::ConvertStringToInt(line);
	}
	else if(mode == 1){
		std::getline(config_stream, line);
		code_pointer = (bool) RLBinUtils::ConvertStringToInt(line);
	}

	std::getline(config_stream, line);
	if(line == "quiet")
		verbosity = 0;
	else if(line == "normal")
		verbosity = 1;
	else
		verbosity = 2;

	if(mode == 3)
	{
		verbosity = 0;
	}

	RLBinUtils::SetVerbosityAndMode(verbosity, mode);
	return;
}

