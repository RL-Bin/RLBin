/**
 * @file Modules.cpp
 * @brief Defines the body of functions in Modules class.
 */

#include <Windows.h>
#include <Psapi.h>
#include <tchar.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <cstring>
#include <map>

#include "..\..\include\Parser\parse.h"
#include "..\..\include\SubUnits\Modules\Modules.h"
#include "..\..\include\SubUnits\Modules\ModuleInfo.h"

using namespace peparse;

// inititalizing the only instace of class 
Modules* Modules::s_instance = NULL;

/** Difference between the static and dynamic base of the module */
ADDRESS g_base_difference;

/**
 * @brief This function iterates over all exported functions and extracts the names and put them in modules
 *	 
 * @param [in] _ignore Ignore it
 * @param [in] _function_address The address of the exported function
 * @param [in] _module_name The name of the DLL or EXE file
 * @param [in] _function_name The name of the exported module
 * @return zero unless the module cannot be found
 */
int printExps(void *_ignore, VA _function_address, std::string &_module_name, std::string &_function_name) 
{
	ADDRESS add = (ADDRESS) _function_address;
	add = add + g_base_difference;
	Modules::Get()->AddExpFunc(add, _function_name);
	return 0;
}

Modules* Modules::Create(void) 
{
	if (s_instance != NULL)
	{
		RLBinUtils::RLBin_Error("An instance of Modules exists", __FILENAME__, __LINE__);
		return NULL;
	}
	RLBinUtils::RLBin_Log("Modules Created!", __FILENAME__);
	s_instance = new Modules();
	return s_instance;
}

Modules* Modules::Get(void) 
{
	if (s_instance == NULL)
	{
		RLBinUtils::RLBin_Error("Modules is not initialized yet!", __FILENAME__, __LINE__);
		return NULL;
	}
	return s_instance;
}

void Modules::Initialize(void) 
{
	// handles to each module in the process
	HMODULE module_handles[1024];

    // handle to current process
    HANDLE current_process_handle;

    // Number of module handles
    DWORD modules_handles_num;

    // Get a handle to the process
    current_process_handle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, GetCurrentProcessId());
    if (NULL == current_process_handle)
    {
    	RLBinUtils::RLBin_Error("Cannot get handle to process with the following id : " + 
    		RLBinUtils::ConvertIntToString(GetCurrentProcessId()), __FILENAME__, __LINE__);
    	return;
    }

   	// Get a list of all the module handles in the current process
    if( EnumProcessModules(current_process_handle, module_handles, sizeof(module_handles), &modules_handles_num))
    {
        for (int i = 0; i < (modules_handles_num / sizeof(HMODULE)); i++ )
        {
            TCHAR module_name[MAX_PATH];
            
            // extract the information from the module
            if ( GetModuleFileNameEx( current_process_handle, module_handles[i], module_name, sizeof(module_name) / sizeof(TCHAR))) 
            {
				MODULEINFO module_info;
				memset(&module_info, 0, sizeof(module_info));
                GetModuleInformation(GetCurrentProcess(), module_handles[i], &module_info, sizeof(module_info));
                
                // adding the new module to the list of modules
                ModuleInfo current_module((SIZE_TYPE)module_info.SizeOfImage, (ADDRESS)module_info.lpBaseOfDll,
                	(ADDRESS)module_info.EntryPoint, RLBinUtils::GetBaseFileName(module_name));
				modules.insert(modules.end(), current_module);
				
				// Using peparse library to extract function names and address to them to each module
				parsed_pe *pkernel = ParsePEFromFile(module_name);
				ADDRESS kernel_base = (ADDRESS) pkernel->peHeader.nt.OptionalHeader.ImageBase;
				g_base_difference = (ADDRESS)module_info.lpBaseOfDll - kernel_base;  
				IterExpVA(pkernel, printExps, NULL);

				// The first module is the main program
				if (i == 0)
					main_module = current_module;
            }
        }
    }
	return;
}

void Modules::AddExpFunc(ADDRESS add, std::string _function_name)
{
	bool lib_call_found = false;
	for (std::list<ModuleInfo>::iterator it = modules.begin(); it != modules.end(); it++)
	{
		if((add > it->base_address) && (add <= (it->base_address + it->module_size)))
		{
			lib_call_found = true;
			it->func[add] = _function_name;
		}
	}
	if(!lib_call_found)
	{
		RLBinUtils::RLBin_Error("module not found for address \t" + _function_name + "\t"  +RLBinUtils::ConvertHexToString(add) + "\n", __FILENAME__, __LINE__);
	}
}
