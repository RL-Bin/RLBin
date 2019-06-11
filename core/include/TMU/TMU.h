/**
 * @file TMU.h
 * @brief This file contains TMU class which controls and manages all other core classes
 */

#ifndef _TMU_H
#define _TMU_H

#include "..\SubUnits\Utils\defs.h"
#include "..\SubUnits\Utils\RLBinUtils.h"

/**
 * @class TMU
 * @brief class that manages and controls all other core modules
 */
class TMU
{
public:
	/** @brief Creates the single instance of the TMU class */
	static TMU* Create(void);

	/** @brief gets the single instance of the TMU class */
	static TMU* Get(void);

	/** @brief initializes TMU class*/
	static void Initialize(void);

private:
	/** The single unique object of this class */
	static TMU* s_instance;
};

#endif