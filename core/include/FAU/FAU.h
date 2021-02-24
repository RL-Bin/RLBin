/**
 * @file FAU.h
 * @brief This file contains FAU class which controls and manages all other core classes
 */

#ifndef _FAU_H
#define _FAU_H

#include "..\SubUnits\Utils\defs.h"
#include "..\SubUnits\Utils\RLBinUtils.h"

/**
 * @class FAU
 * @brief class that manages and controls all other core modules
 */
class FAU
{
public:
	/** @brief Creates the single instance of the FAU class */
	static FAU* Create(void);

	/** @brief gets the single instance of the FAU class */
	static FAU* Get(void);

	/** @brief initializes FAU class*/
	void Initialize(void);

	/** @brief Prints the value of counters to optstat file at the end of program execution*/
	void PrintCounters(void);

	/** @brief Counting total number of excpetions*/
	int count__total;

	/** @brief Counting excpetions for discovering new code */
	int count__new_code;

	/** @brief Counting mishandled check */
	int count__handle_missed;

	/** @brief Counting recurring checks for ret 0xC3 */
	int count__check_0xC3;

	/** @brief Counting recurring checks for ret 0xF2C3 */
	int count__check_0xF2C3;

	/** @brief Counting recurring checks for ret 0xC2 */
	int count__check_0xC2;

	/** @brief Counting recurring checks for calls that go through IAT 0xFF15 */
	int count__check_0xFF15;

	/** @brief Counting recurring checks for jumps that go through IAT 0xFF25 */
	int count__check_0xFF25;

	/** @brief Counting recurring checks for indirect calls 0xFFD */
	int count__check_0xFFD;

	/** @brief Counting recurring checks for indirect calls 0xFF5 disp8 */
	int count__check_0xFF5;

	/** @brief Counting recurring checks for indirect jumps 0xFFE */
	int count__check_0x3EFFE;

	/** @brief Counting recurring checks for indirect jumps with sib */
	int count__check_0xFF2485;

private:
	/** The single unique object of this class */
	static FAU* s_instance;
};

#endif