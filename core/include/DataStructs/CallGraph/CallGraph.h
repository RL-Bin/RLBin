/**
 * @file CallGraph.h
 * @brief This file contains CallGraph class which keeps the data structure for callgraph
 */

#ifndef _CALL_GRAPH_H
#define _CALL_GRAPH_H

#include "..\..\SubUnits\Utils\defs.h"
#include "..\..\SubUnits\Utils\RLBinUtils.h"

/**
 * @class CallGraph
 * @brief class that keeps the data structure for callgraph
 */
class CallGraph
{
public:
	/** @brief Creates the single instance of the CallGraph class */
	static CallGraph* Create(void);

	/** @brief gets the single instance of the CallGraph class */
	static CallGraph* Get(void);

	/** @brief initializes CallGraph module*/
	static void Initialize(void);

private:
	/** The single unique object of this class */
	static CallGraph* s_instance;
};

#endif