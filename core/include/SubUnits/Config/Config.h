#ifndef _CONFIG_H
#define _CONFIG_H

/** @file Config.h
 * @brief Contains Config class which handles reading from configuration file.
 *  
 * This file contains the class which has the information of the config file.
 * Also it will load default configuration if the config file is not available.
 */

#include <map>
#include <string>

#include "..\..\SubUnits\Utils\defs.h"
#include "..\..\SubUnits\Utils\RLBinUtils.h"

/**
 * @class Config
 * @brief This class has the information of the config file
 */
class Config
{
public:
	/**
	 * @brief Creates the one and only instance of Config class
	 *
	 * @return Config* The pointer to the static Config object
	 */
	static Config* Create(void);

	/**
	 * @brief Gets the one and only instance of StaticAnalyzer class
	 *
	 * @return StaticAnalyzer* The pointer to the static StaticAnalyzer object
	 */
	static Config* Get(void);

	/** Reads configuration from config file */
	void Initialize(void);

	/** 
	 * @brief Checks if a feature is enabled 
	 *
	 * @param [in] feature The featue to be checked
	 * @return the value of the feature
	 */
	int GetFeatureValue(std::string feature);

	/** Prints the config file, used for debugging only*/
	void PrintConfigs();

private:

	/** Map containing config options and their values */
	std::map<std::string,int> conf;

	/** The single unique object of this class */
	static Config* s_instance;
};

#endif