/** @file core.cpp
 * @brief Initializes and Finalizes RL-Bin core modules 
 *
 * This source file contains the main functions of core RL-Bin
 * It is responsible to initialize and finalize different modules.
 */

#include <Windows.h>
#include <Psapi.h>

#include "..\include\SubUnits\Utils\defs.h"
#include "..\include\SubUnits\Utils\RLBinUtils.h"

#include "..\include\CU\CU.h"
#include "..\include\StatUnit\StatUnit.h"
#include "..\include\SubUnits\Config\Config.h"

extern LONG WINAPI RLBinExceptionHandler(PEXCEPTION_POINTERS p);

extern void InitGlobals();

/** @brief This function initalizes core modules based on mode of operation */
extern "C" DEFAULT_VISIBILTY void StartRLBin()
{	
	// Starting and initiating RLBin classes
	RLBinUtils::RLBin_Log("RL-Bin : Starting RL-Bin Core", __FILENAME__);
	RLBinUtils::RLBin_Log("Process ID is   :     " + RLBinUtils::ConvertIntToString(GetCurrentProcessId()), __FILENAME__);

	// register exception handler
	AddVectoredExceptionHandler(1, RLBinExceptionHandler);

	ISSTATIC
	{
		StatUnit::Create();
		StatUnit::Get()->Run();
		ExitProcess(0);
	}

	ISDYNAMIC
	{
		CU::Create();
		CU::Get()->Initialize();
		InitGlobals();
	}

	return;
}

/** @brief This function finializes and gets report from core modules based on mode of operation */
extern "C" DEFAULT_VISIBILTY void FinalizeRLBin()
{
	ISDYNAMIC
	{
		CU::Get()->Finalize();
	}
	// Finalizing and wrapping up RLBin classes
	RLBinUtils::RLBin_Log(std::string("Finalizing RL-Bin "), __FILENAME__);

	return;
}