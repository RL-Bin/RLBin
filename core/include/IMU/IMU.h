/**
 * @file IMU.h
 * @brief This file contains IMU class which controls and manages all other core classes
 */

#ifndef _IMU_H
#define _IMU_H

#include <unordered_map>

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

	/** (Temp) Address of Ret Routine */
	ADDRESS RetRoutine;

	/** @brief Creates the appropriate intrumentation routine to check target of the indirect CTI instruction
	 *
	 * return The address of the created routine
	 */
	ADDRESS CreateInstRoutine(ADDRESS _address);

	/** @brief Print all inst routines*/
	void PrintRoutines();

private:

	/** @brief Creates a routine to check target of a return instruction
	 *
	 * return The address of the created routine
	 */
	ADDRESS CreateInstRoutine_0xC3();

	/** @brief Creates a routine to check target of indirect calls that go through IAT
	 *
	 * param [in] the addresss of the indirect call
	 * return The address of the created routine
	 */
	ADDRESS CreateInstRoutine_0xFF15(ADDRESS _address);

	/** The single unique object of this class */
	static IMU* s_instance;

	/** Memory space containing our instrumentation routines */
	byte *instrumentations;

	/** Beginning of empy space */
	ADDRESS head;

	/** @brief The map that contains instrumentation for checking an indirect CTI */
	std::unordered_map<DWORD64,ADDRESS> inst_map; 
};

#endif