/**
 * @file TMU.h
 * @brief This file contains TMU class which controls and manages all other core classes
 */

#ifndef _TMU_H
#define _TMU_H

#include <unordered_map>

#include "..\SubUnits\Utils\defs.h"
#include "..\SubUnits\Utils\RLBinUtils.h"

#include "Trampoline.h"

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
	 * @brief Inserts trampoline at the given address to discover it dynamically
	 *
	 * @param[in] _address Address of the trampoline
	 */
	void InsertTrampoline(ADDRESS _address);

	/**
	 * @brief Inserts trampoline at the given address to our instrumentation
	 *
	 * @param[in] _address Address of the trampoline
	 * @param[in] _instr Address of the instrumentation routine
	 * @param[in] p Pointer to the context
	 */
	void InsertCheckTrampoline(ADDRESS _address, ADDRESS _instr, PEXCEPTION_POINTERS p);

	/**
	 * @brief Removes trampoline from the given address
	 *
	 * @param[in] _address Address of the code to be restored
	 */
	void RemoveTrampoline(ADDRESS _address);

	/** @brief Removes all trampolines Inserted in the code */
	void RemoveAllTrampolines();
	
	/** @brief The map that contains backup of rewritten code */
	std::unordered_map<ADDRESS, byte> tramps_cc;

	/** @brief The map that contains backup of rewritten code */
	std::unordered_map<ADDRESS, Trampoline> tramps_e9;

	/** @brief The map that is used for redirection between ind cti and instrumentation */
	std::unordered_map<ADDRESS,ADDRESS> redirect_map; 

private:

	/** @brief The single unique object of this class */
	static TMU* s_instance;

	/** @brief Prints all trampolines to the debug file */
	void ListTrampolines();
};

#endif