#ifndef _MODULES_H
#define _MODULES_H

/**
 * @file Modules.h
 * @brief This file contains Modules class which manages and handles the modules loaded on the memory
 */

#include "..\..\SubUnits\Utils\defs.h"
#include "..\..\SubUnits\Utils\RLBinUtils.h"

/**
 * @class Modules
 * @brief Modules class contains disassmebly functions
 */
class Modules
{
public:
	/** @brief Creates the single instance of the Modules class */
	static Modules* Create(void);

	/** @brief gets the single instance of the Modules class */
	static Modules* Get(void);

	/** @brief initializes Modules module*/
	static void Initialize(void);

private:
	/** The single unique object of this class */
	static Modules* s_instance;
};

#endif