#ifndef _TIMER_H
#define _TIMER_H

/**
 * @file Timer.h
 * @brief This file contains Timer class which has the responsibitly to measeure and report time
 */

#include "..\..\SubUnits\Utils\defs.h"
#include "..\..\SubUnits\Utils\RLBinUtils.h"

/**
 * @class Timer
 * @brief This class has the information of the timer and measurements
*/
class Timer
{
public:
	/** @brief Creates the single instance of the Timer class */
	static Timer* Create(void);

	/** @brief gets the single instance of the Timer class */
	static Timer* Get(void);

	/** @brief initializes Timer module*/
	static void Initialize(void);

private:
	/** The single unique object of this class */
	static Timer* s_instance;
};

#endif