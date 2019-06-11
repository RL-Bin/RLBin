/**
 * @file DisTable.h
 * @brief This file contains Funcs class which keeps the data structure for disassmebly table
 */

#ifndef _DIS_TABLE_H
#define _DIS_TABLE_H

#include "..\..\SubUnits\Utils\defs.h"
#include "..\..\SubUnits\Utils\RLBinUtils.h"

/**
 * @class DisTable
 * @brief class that keeps the data structure for disassmebly table
 */
class DisTable
{
public:
	/** @brief Creates the single instance of the DisTable class */
	static DisTable* Create(void);

	/** @brief gets the single instance of the DisTable class */
	static DisTable* Get(void);

	/** @brief initializes DisTable module*/
	static void Initialize(void);

private:
	/** The single unique object of this class */
	static DisTable* s_instance;
};

#endif