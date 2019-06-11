/**
 * @file CallGraph.cpp
 * @brief Defines the body of functions in CallGraph class.
 */

#include "..\..\include\DataStructs\CallGraph\CallGraph.h"

// inititalizing the only instace of class 
CallGraph* CallGraph::s_instance = NULL;

CallGraph* CallGraph::Create(void) 
{
	if (s_instance != NULL)
	{
		RLBinUtils::RLBin_Error("An instance of CallGraph exists", __FILENAME__, __LINE__);
		return NULL;
	}
	s_instance = new CallGraph();
	return s_instance;
}

CallGraph* CallGraph::Get(void) 
{
	if (s_instance == NULL)
	{
		RLBinUtils::RLBin_Error("CallGraph is not initialized yet!", __FILENAME__, __LINE__);
		return NULL;
	}
	return s_instance;
}

void CallGraph::Initialize(void) 
{

}
