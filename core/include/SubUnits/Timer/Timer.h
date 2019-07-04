#ifndef _TIMER_H
#define _TIMER_H

/**
 * @file Timer.h
 * @brief This file contains Timer class which has the responsibitly to measeure and report time
 */

#include <map>
#include <chrono>
#include <string>

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

	/** Default destuctor of Timer class */		
	~Timer(){}

	/** This function intializes the name of the timers */
	void Initialize();

	/** 
	 * @brief This function creates and initialize a new timer 
	 *
	 * @param [in] _timer_name The name of the new timer that is created
	 * @return int id of the timer created
	 */	
	int GetNewTimer(std::string _timer_name);

	/** 
	 * @brief this function starts a new time measurement for the given timer 
	 *
	 * @param [in] _timer_id shows the id of the timer to start
	 */
	void Start(int _timer_id);

	/** 
	 * @brief this function stops current time measurement for the given timer 
	 *
	 * @param [in] _timer_id shows the id of the timer to stop
	 */
	void Stop(int _timer_id);

	/** 
	 * @brief this function prints the average of the time intervals measured by given timer 
	 *
	 * @param [in] _timer_id shows which timer to print
	 * @param [in] _log_type shows which log file to print to
	 */
	void PrintAverageTime(int _timer_id, LogType _log_type);

private:
	/** The one and only static instance of Optimizer class */
	static Timer *s_instance;

	/** The number of timers currently in use */
	int used_timers;

	/** The name of the timers */
	std::string timer_names[MAX_TIME_COUNT];

	/** The number of times each timer has been used */
	int counted_times[MAX_TIME_COUNT];

	/** The average of times each timer has measured */
	__int64 average_times[MAX_TIME_COUNT];

	/** The start time of the time which is currently being measured */
	std::chrono::steady_clock::time_point start_time[MAX_TIME_COUNT];
};

#endif