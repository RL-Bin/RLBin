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

	/** 
	 * @brief adds the given section to the corresponding module
	 *
	 * @param [in] The section info to be added
	 */
	void AddSection(SectionInfo sec);

	/** 
	 * @brief gets the entry point of the main module
	 *
	 * @return The entry point
	 */
	ADDRESS GetEntryPoint();

	/** @brief Prints brief information of each module in the modules file*/
	void PrintModulesShort();

	/** Get the main module (program)*/
	ModuleInfo *GetMainModule();

	/** 
	 * @brief checks if an address is within the code section
	 *
	 * @param [in] The address to be checked
	 * @return true if the address is withing the the text section
	 */
	bool IsInsideMainCode(ADDRESS address);

private:
	/** The list of all modules (Program and DLL) loaded into the program address space */
	std::list<ModuleInfo> modules;

	/** The single unique object of this class */
	static Modules* s_instance;

	/** @brief Prints the information of the main file to the log file*/
	void PrintInfoLogFile();
};

#endif