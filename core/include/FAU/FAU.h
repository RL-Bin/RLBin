/**
 * @file FAU.h
 * @brief This file contains FAU class which controls and manages all other core classes
 */

#ifndef _FAU_H
#define _FAU_H

#include "..\SubUnits\Utils\defs.h"
#include "..\SubUnits\Utils\RLBinUtils.h"

/**
 * @class FAU
 * @brief class that manages and controls all other core modules
 */
class FAU
{
public:
	/** @brief Creates the single instance of the FAU class */
	static FAU* Create(void);

	/** @brief gets the single instance of the FAU class */
	static FAU* Get(void);

	/** @brief initializes FAU class*/
	static void Initialize(void);

private:
	/** The single unique object of this class */
	static FAU* s_instance;
};

#endif