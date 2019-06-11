#ifndef _CONFIG_H
#define _CONFIG_H

/** @file Config.h
 * @brief Contains Config class which handles reading from configuration file.
 *  
 * This file contains the class which has the information of the config file.
 * Also it will load default configuration if the config file is not available.
 */

#include "..\..\SubUnits\Utils\defs.h"
#include "..\..\SubUnits\Utils\RLBinUtils.h"

/**
 * @class Config
 * @brief This class has the information of the config file
 */
class Config
{
public:
	/** @brief Creates the single instance of the Config class */
	static Config* Create(void);

	/** @brief gets the single instance of the Config class */
	static Config* Get(void);

	/** @brief initializes Config module*/
	static void Initialize(void);

private:
	/** The single unique object of this class */
	static Config* s_instance;
};

#endif