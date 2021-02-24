/**
 * @file StatUnit.h
 * @brief This file contains StatUnit class which dumps static disassembly
 */

#ifndef _STAT_UNIT_H
#define _STAT_UNIT_H

#include <list>

#include "..\SubUnits\Utils\defs.h"
#include "..\SubUnits\Utils\RLBinUtils.h"

/**
 * @class StatUnit
 * @brief class that dumps static disassembly by recursice traversal
 */
class StatUnit
{
public:
	/** @brief Creates the single instance of the StatUnit class */
	static StatUnit* Create(void);

	/** @brief gets the single instance of the StatUnit class */
	static StatUnit* Get(void);

	/** @brief runs the static disassmebler*/
	void Run(void);

private:
	/** The single unique object of this class */
	static StatUnit* s_instance;

	/** List of addresses that are disassembled */
	std::list<ADDRESS> disassembled;

	/** List of addresses that will be disassembled */
	std::list<ADDRESS> to_be_disassembled;

	/** List of addresses that are called directly */
	std::list<ADDRESS> static_funcs;

	/** @brief Disassmeble the binary using recursive traversal*/
	void RecursiveDisassembly();

	/** @brief Prints the disassembly to file*/
	void PrintDisassembly();

	/** 
	 * @brief Checks to see if a given address is in a list
	 * 
	 * param [in] the list to be checked
	 * param [in] the address to be checked
	 * return true if the item is in the list 
	 */
	bool CheckList(std::list<ADDRESS> input_list, ADDRESS to_be_checked);

	/** @brief Add data references to the code segment as starting point of disassembly */
	void AddDataRefs();

	/** 
	 * @brief checks if an instruction is valid and the target is within the code section
	 *
	 * @param [in] The address to be checked
	 * @return true if inst is valid
	 */
	bool IsValidInstAndTarget(ADDRESS address);
};

#endif