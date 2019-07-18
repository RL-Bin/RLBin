/**
 * @file TMU.h
 * @brief This file contains TMU class which controls and manages all other core classes
 */

#ifndef _TMU_H
#define _TMU_H

#include <unordered_map>

#include "..\SubUnits\Utils\defs.h"
#include "..\SubUnits\Utils\RLBinUtils.h"

/**
 * @class TMU
 * @brief class that manages and controls all other core modules
 */
class TMU
{
public:
	/** @brief Creates the single instance of the TMU class */
	static TMU* Create(void);

	/** @brief gets the single instance of the TMU class */
	static TMU* Get(void);

	/** @brief initializes TMU class*/
	void Initialize(void);

	/**
	 * @brief Inserts trampoline at the given address
	 *
	 * @param[in] _address Address of the trampoline
	 */
	void InsertTrampoine(ADDRESS _address);

	/**
	 * @brief Removes trampoline from the given address
	 *
	 * @param[in] _address Address of the code to be restored
	 */
	void RemoveTrampoine(ADDRESS _address);

private:

	/** The map that contains backup of rewritten code */
	std::unordered_map<ADDRESS,byte> original_code;

	/** The single unique object of this class */
	static TMU* s_instance;
};

#endif