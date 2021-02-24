#ifndef _TRAMPOLINE_H
#define _TRAMPOLINE_H

/**
 * @file Trampoline.h
 * @brief This file contains Trampoline class which has the functions and information of all trampoines inserted
 */

#include "..\SubUnits\Utils\defs.h"
#include "..\SubUnits\Utils\RLBinUtils.h"

#include "..\SubUnits\Disassembler\Disassembler.h"

/**
@class Trampoline
@brief class which has the functions and information of all trampoines inserted
*/
struct Trampoline
{
public:
	/** @brief The original code that the trampoline replaced */
	BYTE original_code[8];

	/** @brief The size of the trampoline */
	BYTE size;
};	

#endif