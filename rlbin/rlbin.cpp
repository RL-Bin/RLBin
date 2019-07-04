/** @file rlbin.cpp
    @brief Creates target process and injects RL-Bin
    
	Defines the entry point for the console application.
	This application will start the taget process in suspended mode.
	Then it will inject inject.dll into the target process.
	After that it will resume the process and wait unitl it finishes.
*/

#include <iostream>
#include <Windows.h>
#include <fstream>
#include <string>
#include <Psapi.h>

#include "..\core\include\SubUnits\Utils\defs.h"
#include "..\core\include\SubUnits\Utils\RLBinUtils.h"
#include "..\core\include\SubUnits\Timer\Timer.h"

/** Global variable used to pass the information of the process that is created. */
PROCESS_INFORMATION g_pInfo;

/**
 * @brief Creates the target process with same startup attribute
 * @param [in] programName The name of target application and its arguments
 * @return true if the target can be created successfully
 */
bool InitProcess(LPSTR target_cmd) 
{
	STARTUPINFOA startInfo;

	// Getting the startup info of the current process to pass the same info to target process 
	GetStartupInfoA(&startInfo);

	//now we have the process command to execute, create the process, suspended with attribute CREATE_SUSPENDED
	bool ret = CreateProcessA(NULL, target_cmd, NULL, NULL, FALSE, CREATE_SUSPENDED, NULL, NULL, &startInfo, &g_pInfo);
	return ret;
}

/**
 * @brief The entry point for monitoring process
 * @param [in] argc the number of arguments passed to target plus one   
 * @param [in] argv the first argument is the target, the rest are arguments to the target
 * @return program execution status
 */
int main(int argc, char *argv[])
{
	// First, initialize and set the timers
	Timer::Create();
	Timer::Get()->Initialize();

	/** The timer id for the whole program */
	int total_timer_id = Timer::Get()->GetNewTimer("Prgram");

	RLBinUtils::Init();

	if (argc < 2)
	{
		RLBinUtils::RLBin_Error("File name of the target application is not provided. RL-Bin will exit! \n", __FILENAME__, __LINE__);
		return 0;
	}

	char *fileName = argv[1];

	RLBinUtils::CheckFileExists(fileName, "Target application cannot be found. RL-Bin will exit! \n");

	//RLBinUtils::CheckFileExists(INJECT_LIB_NAME, "inject.dll cannot be found in ./bin folder. RL-Bin will exit! \n");

	RLBinUtils::CheckFileExists(CORE_LIB_NAME, "core.dll cannot be found in ./bin folder. RL-Bin will exit! \n");
	

	LPSTR cmd_line = GetCommandLineA();

	LPSTR target_cmd = (LPSTR) (cmd_line + strlen(argv[0]) + 2);

	// Create the target process, exit if it cannot be created.
	if(!InitProcess(target_cmd))
	{
		RLBinUtils::RLBin_Error("The target process cannot be created! \n", __FILENAME__, __LINE__);
		return 0;	
	}
	else
	{
		RLBinUtils::RLBin_Log("Created target process to be monitored!", __FILENAME__);
	}

	// path to inject dll
	LPCSTR DllPath = CORE_LIB_NAME;

	int procID = g_pInfo.dwProcessId;
	// Open a handle to target process
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procID);

	// Allocate memory for the dllpath in the target process
	// length of the path string + null terminator
	LPVOID pDllPath = VirtualAllocEx(hProcess, 0, strlen(DllPath) + 1,
		MEM_COMMIT, PAGE_READWRITE);

	// Write the path to the address of the memory we just allocated
	// in the target process
	WriteProcessMemory(hProcess, pDllPath, (LPVOID)DllPath,
		strlen(DllPath) + 1, 0);

	// Create a Remote Thread in the target process which
	// calls LoadLibraryA as our dllpath as an argument -> program loads our dll
	HANDLE hLoadThread = CreateRemoteThread(hProcess, 0, 0,
		(LPTHREAD_START_ROUTINE)GetProcAddress(GetModuleHandleA("Kernel32.dll"),
			"LoadLibraryA"), pDllPath, 0, 0);

	// Wait for the execution of our loader thread to finish
	WaitForSingleObject(hLoadThread, INFINITE);

	// Free the memory allocated for our dll path
	VirtualFreeEx(hProcess, pDllPath, strlen(DllPath) + 1, MEM_RELEASE);

	// Resume the execution of the target process after dll is injected and initialized
	ResumeThread(g_pInfo.hThread);

	// Wait for the target process, then kill the monitoring process
	WaitForSingleObject(g_pInfo.hThread, INFINITE);

	RLBinUtils::RLBin_Log("Target process executed successfully. Terminating RL-Bin monitoring process!", __FILENAME__);

	// Finally, measure the timers at the end of exection
	Timer::Get()->Stop(total_timer_id);
	Timer::Get()->PrintAverageTime(total_timer_id, T_LOG);

	return 0;
}