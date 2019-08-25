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
	void Initialize(void);

	/** @brief Creates a routine to check target of a return instruction
	 *
	 * return The address of the created routine
	 */
	ADDRESS CreateInstRoutineRet();

	/** (Temp) Address of Ret Routine */
	ADDRESS RetRoutine;

private:
	/** The single unique object of this class */
	static IMU* s_instance;

	/** Memory space containing our instrumentation routines */
	byte *instrumentations;

	/** Beginning of empy space */
	ADDRESS head;
};

#endif