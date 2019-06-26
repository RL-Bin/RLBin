#ifndef _MODULE_INFO_H
#define _MODULE_INFO_H

/**
 * @file ModuleInfo.h
 * @brief This file contains ModuleInfo class which has the information of the loaded modules
 */

#include <map>
#include <string>

#include "..\..\SubUnits\Utils\defs.h"
#include "..\..\SubUnits\Utils\RLBinUtils.h"


/**
 * @class SectionInfo
 * @brief This class has the information of each section in a PE file
 */
class SectionInfo
{
public:
	std::string name;
	ADDRESS base;
	SIZE_TYPE size;
};

/**
 * @class ModuleInfo
 * @brief This class has the information of the loaded modules
 */
class ModuleInfo
{
public:
	/** Default constuctor of ModuleInfo class */
	ModuleInfo(){}
	
	/** @brief Constructor which initialize all module information 
	 *
	 * @param [in] _module_size The size of the module
	 * @param [in] _base_address The base address of the module
	 * @param [in] _entry_point The entry point of the module
	 * @param [in] _name The base name of the module
	 */
	ModuleInfo(SIZE_TYPE _module_size, ADDRESS _base_address, ADDRESS _entry_point, std::string _name)
	{
		module_size = _module_size;
		base_address = _base_address;
		entry_point = _entry_point;
		name = _name;
	}

	/** Size of the module */		
	SIZE_TYPE module_size;

	/** The starting address of the module */		
	ADDRESS base_address;

	/** The entry point of the module */		
	ADDRESS entry_point;

	/** Name of the dll or program */		
	std::string name;

	/** list of the exported functions of the module */		
	std::map<ADDRESS,std::string> func;

	/** list of the exported functions of the module */		
	std::list<SectionInfo> sections;
};	

#endif