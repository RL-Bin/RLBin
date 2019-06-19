#ifndef _MODULES_H
#define _MODULES_H

/**
 * @file Modules.h
 * @brief This file contains Modules class which manages and handles the modules loaded on the memory
 */

#include <map>
#include <list>
#include <string>

#include "..\..\SubUnits\Utils\defs.h"
#include "..\..\SubUnits\Utils\RLBinUtils.h"

#include "ModuleInfo.h"

/**
 * @class Modules
 * @brief class that manages and handles the modules loaded on the memory
 */
class Modules
{
public:
	/**
	 * @brief Creates the one and only instance of ModuleHs class
	 *
	 * @return Modules* The pointer to the static Modules object
	 */
	static Modules* Create(void);

	/**
	 * @brief Gets the one and only instance of Modules class
	 *
	 * @return Modules* The pointer to the static Modules object
	 */
	static Modules* Get(void);

	/** @brief initializes Modules module*/
	void Initialize(void);

	/** 
	 * @brief adds exported function to a module
	 *
	 * @param [in] The address of the function to be added
	 * @param [in] The name of the function
	 */
	void AddExpFunc(ADDRESS add, std::string _function_name);

private:
	/** The list of all modules (Program and DLL) loaded into the program address space */
	std::list<ModuleInfo> modules;
	
	/** The main module (program) loaded into memory */
	ModuleInfo main_module;

	/** The single unique object of this class */
	static Modules* s_instance;
};

#endif