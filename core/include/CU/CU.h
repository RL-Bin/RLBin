/**
 * @file CU.h
 * @brief This file contains CU class which controls and manages all other core classes
 */

#ifndef _CU_H
#define _CU_H

#include "..\SubUnits\Utils\defs.h"
#include "..\SubUnits\Utils\RLBinUtils.h"

/**
 * @class CU
 * @brief class that manages and controls all other core modules
 */
class CU
{
public:
	/** @brief Creates the single instance of the CU class */
	static CU* Create(void);

	/** @brief gets the single instance of the CU class */
	static CU* Get(void);

	/** @brief initializes all other modules*/
	static void Initialize(void);

private:
	/** The single unique object of this class */
	static CU* s_instance;
};

#endif