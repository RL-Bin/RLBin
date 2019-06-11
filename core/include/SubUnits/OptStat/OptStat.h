#ifndef _OPT_STAT_H
#define _OPT_STAT_H

/**
 * @file OptStat.h
 * @brief This file contains OptStat class
 *
 * This class is responsible for collecting stats and doing optimization
 */

#include "..\..\SubUnits\Utils\defs.h"
#include "..\..\SubUnits\Utils\RLBinUtils.h"

/**
 * @class OptStat
 * @brief This clss contains the class which collects stats and does optimization
 */
class OptStat
{
public:
	/** @brief Creates the single instance of the OptStat class */
	static OptStat* Create(void);

	/** @brief gets the single instance of the OptStat class */
	static OptStat* Get(void);

	/** @brief initializes OptStat module*/
	static void Initialize(void);

private:
	/** The single unique object of this class */
	static OptStat* s_instance;
};

#endif