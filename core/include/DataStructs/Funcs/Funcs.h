/**
 * @file Funcs.h
 * @brief This file contains Funcs class which keeps the data structure for functions
 */

#ifndef _FUNCS_H
#define _FUNCS_H

#include "..\..\SubUnits\Utils\defs.h"
#include "..\..\SubUnits\Utils\RLBinUtils.h"

/**
 * @class Funcs
 * @brief class that keeps the data structure for functions
 */
class Funcs
{
public:
	/** @brief Creates the single instance of the Funcs class */
	static Funcs* Create(void);

	/** @brief gets the single instance of the Funcs class */
	static Funcs* Get(void);

	/** @brief initializes Funcs modules*/
	static void Initialize(void);

private:
	/** The single unique object of this class */
	static Funcs* s_instance;
};

#endif