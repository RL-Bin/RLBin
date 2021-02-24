/**
 * @file Timer.cpp
 * @brief Defines the body of functions in Timer class.
 */

#include <chrono>
#include <sstream>
#include <utility> 
#include <iostream>

#include "..\..\include\SubUnits\Timer\Timer.h"

// inititalizing the only instace of class 
Timer* Timer::s_instance = NULL;

Timer* Timer::Create(void) 
{
	if (s_instance != NULL)
	{
		RLBinUtils::RLBin_Error("An instance of Timer exists", __FILENAME__, __LINE__);
		return NULL;
	}
	s_instance = new Timer();
	return s_instance;
}

Timer* Timer::Get(void) 
{
	if (s_instance == NULL)
	{
		RLBinUtils::RLBin_Error("Timer is not initialized yet!", __FILENAME__, __LINE__);
		return NULL;
	}
	return s_instance;
}

void Timer::Initialize()
{
	// setting the number of used timers and initializing them with empty string 
	used_timers = -1;
	for(int i=0; i<MAX_TIME_COUNT;i++)
	{
		timer_names[i] = "";
	}
}

int Timer::GetNewTimer(std::string _timer_name)
{
	// check if the timer has been initialized before
	for(int i=0; i<(used_timers+1);i++)
	{
		if(_timer_name == timer_names[i])
		{
			return i;
		}
	}

	// If it's not initialized, create a new timer
	used_timers = used_timers + 1;

	// check to see if there is enough room for a new timer
	if(used_timers == MAX_TIME_COUNT)
	{
		RLBinUtils::RLBin_Error("No more timers left!", __FILENAME__, __LINE__);
	}

	timer_names[used_timers] = _timer_name; 	
	average_times[used_timers] = 0;
	start_time[used_timers] = std::chrono::high_resolution_clock::now();
	counted_times[used_timers] = 0;

	// return the id of the newly created timer
	return used_timers;
}

void Timer::Start(int _timer_id)
{
	start_time[_timer_id] = std::chrono::high_resolution_clock::now();
}

void Timer::Stop(int _timer_id)
{
	std::chrono::steady_clock::time_point stop_time = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop_time-start_time[_timer_id]).count();
	counted_times[_timer_id] ++; 

	// recalculating the average time by considering the new time that is measured
	average_times[_timer_id] = ((average_times[_timer_id] * (counted_times[_timer_id] -1)) + duration)/counted_times[_timer_id];
}

void Timer::PrintAverageTime(int _timer_id, LogType _log_type)
{
	// Printing the average in miliseconds
	std::stringstream ss;
    ss << (average_times[_timer_id]/1000000) << " ms, " << (average_times[_timer_id]%1000000) << " ns";
	RLBinUtils::RLBin_Multi(timer_names[_timer_id] + " execution took " + ss.str(), _log_type);
}