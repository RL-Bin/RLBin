#ifndef _DISASSEMBLER_H
#define _DISASSEMBLER_H

/**
 * @file Disassembler.h
 * @brief This file contains Disassembler class and functions which are responsible for disassembling the code
 */

#include "..\..\SubUnits\Utils\defs.h"
#include "..\..\SubUnits\Utils\RLBinUtils.h"

/**
 * @class Disassembler
 * @brief Disassembler class contains disassmebly functions
 */
class Disassembler
{
public:
	/** @brief Creates the single instance of the Disassembler class */
	static Disassembler* Create(void);

	/** @brief gets the single instance of the Disassembler class */
	static Disassembler* Get(void);

	/** @brief initializes Disassembler module*/
	static void Initialize(void);

private:
	/** The single unique object of this class */
	static Disassembler* s_instance;
};

#endif