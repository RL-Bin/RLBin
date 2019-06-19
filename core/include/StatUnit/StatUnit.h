/**
 * @file StatUnit.h
 * @brief This file contains StatUnit class which dumps static disassembly
 */

#ifndef _STAT_UNIT_H
#define _STAT_UNIT_H

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
	/** @brief Disassmeble the binary using recursive traversal*/
	void Disassemble(void);

	/** The single unique object of this class */
	static StatUnit* s_instance;
};

#endif