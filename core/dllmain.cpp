/** @file inject\dllmain.cpp
 *  @brief Injects core and wraps the analysis
 *
 * 	Contains start and end monitoring functions.
 *	Injects core.dll into the process and acts as a wrapper around the analysis.
 */

#include <stdio.h>
#include <Windows.h>
#include <tlhelp32.h>
#include <Psapi.h>

#include "include/SubUnits/Utils/defs.h"
#include "include/SubUnits/Utils/RLBinUtils.h"
#include "include/SubUnits/Config/Config.h"

/** Typedef for type of function inside RLBin that is used to initiate the monitoring process*/
typedef void (*StartRLBinType)();

/** Typedef for function that closes the processing inside RLBin */
typedef void (*FinalizeRLBinType)();

/**
 * @brief The entry point to the dll
 *
 * This function is called when dll attached and detached
 * to process or threads
 *
 * @param [in] hModule This is the handle to the DLL module
 * @param [in] ul_reason_for_call This is the event that caused the call, such as attach detach
 * @param [in] lpReserved Reserved and not used 
 * @return true all the time
 */
BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved)
{
	// Getting the name and pid of the current process for logging
	HANDLE currentProcessHandle = GetCurrentProcess();
	char processName[100] = { 0 };
	GetModuleBaseNameA(currentProcessHandle, NULL, processName, 100);
	DWORD pId = GetCurrentProcessId();

	switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
		{
			// This needs to be called in every project to find out the current analysis number
			RLBinUtils::ReadAnalysisNumber();

			Config::Initialize();

			RLBinUtils::RLBin_Log(std::string("Inside DllMain of the injected DLL, process name is: ") + std::string(processName), __FILENAME__);
			RLBinUtils::RLBin_Log(std::string("Command Line is: ") + std::string(GetCommandLineA()), __FILENAME__);
			RLBinUtils::RLBin_Log(std::string("Process ID is: ") + std::to_string((int)pId), __FILENAME__);
			RLBinUtils::RLBin_Log("Inside startMonitoring, after code injection", __FILENAME__);	

			void *symFunc = RLBinUtils::CheckLibAndFuncLookup(CORE_LIB_NAME, START_RLBIN_FUNC, false);
			StartRLBinType targetFunc = (StartRLBinType)symFunc;
			(*targetFunc)();
			break;
		}
		case DLL_THREAD_ATTACH:
			break;

		case DLL_THREAD_DETACH:
			break;

		case DLL_PROCESS_DETACH:
		{
			RLBinUtils::RLBin_Log("Inside finalizeMonitoring, after code injection", __FILENAME__);

			void *symFunc = RLBinUtils::CheckLibAndFuncLookup(CORE_LIB_NAME, FINALIZE_RLBIN_FUNC, false);
			FinalizeRLBinType targetFunc = (FinalizeRLBinType)symFunc;
			(*targetFunc)();
			break;
		}
	}
	return TRUE;
}