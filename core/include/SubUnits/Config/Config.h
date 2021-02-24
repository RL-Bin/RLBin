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
	/** Reads configuration from config file */
	static void Initialize(void);

	static int mode;

	static int optlevel;

	static int verbosity;

	static bool code_pointer;
};

#endif