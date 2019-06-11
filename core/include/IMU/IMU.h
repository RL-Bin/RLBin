/**
 * @file IMU.h
 * @brief This file contains IMU class which controls and manages all other core classes
 */

#ifndef _IMU_H
#define _IMU_H

#include "..\SubUnits\Utils\defs.h"
#include "..\SubUnits\Utils\RLBinUtils.h"

/**
 * @class IMU
 * @brief class that manages and controls all other core modules
 */
class IMU
{
public:
	/** @brief Creates the single instance of the IMU class */
	static IMU* Create(void);

	/** @brief gets the single instance of the IMU class */
	static IMU* Get(void);

	/** @brief initializes IMU class*/
	static void Initialize(void);

private:
	/** The single unique object of this class */
	static IMU* s_instance;
};

#endif