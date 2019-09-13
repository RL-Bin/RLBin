#ifndef _RLBINUTILS_H_
#define _RLBINUTILS_H_

/** @file RLBinUtils.h
	@brief Handles all utility functions provided to RL-Bin in RLBinUtils class
	
	This header file contains several utility functions which are
	visible in RL-Bin executable, inject, and core library
*/

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <vector>
#include <cstdlib>
#include <memory>
#include <signal.h>
#include <algorithm>
#include <functional>
#include <cctype>
#include <locale>
#include <Windows.h>

#include "defs.h"

/**
 * @class RLBinUtils
 * @brief A container class to define the utility functions that are used all over RLBin.
 *
 * This class is compiled within each project
 */
class RLBinUtils
{
public:
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////							Implemented in RLBinUtils.cpp						////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/** @brief Initialize the analysis folder for the current execution */
	static DEFAULT_VISIBILTY void Init();

	/** @brief Reads the analysis folder for the current execution */
	static DEFAULT_VISIBILTY void ReadAnalysisNumber();

	/**
	 * @brief Gets the current time
	 *
	 * @return Current time as a string
	 */
	static std::string GetTime(void);

	/**
	 * @brief Appends n given string to eachother
	 *
	 * An utility function to append a set of strings. You need to pass the
	 * number of strings (char *) to be appended, followed by that many char*,
	 * this API appends those and creates a string reference
	 *
	 * @param [in] n Number of char* to be appended
	 * @return std::string Appended string
	 */
	static DEFAULT_VISIBILTY std::string AppendStrings(int n, ...);

	/**
	 * @brief Checks if libName refers to the current application or not.
	 *
	 * NULLSTRING implies current application
	 *
	 * @return true if it is the current application
	 */
	static bool isCurrentApp(const char* libName);

	/**
	 * @brief Get the path of the executable
	 *
	 * Function that returns the complete path of the executable even when it has a symbolic link.
	 *
	 * @return std::string Complete Path
	 */
	static std::string GetSelfPath();

	/**
	 * @brief Get the Name of the current process
	 *
	 * @return std::string Name of the application
	 */
	static std::string GetApplicationName(void);

	/**
	 * @brief Function that gets the number of the last error occured in the application
	 *
	 * @return std::string Number of the last error happened
	 */
	static DEFAULT_VISIBILTY  std::string GetLastErrorString(void);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////						Implemented in FileOperations.cpp						////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/**
	 * @brief Opens a file and checks for errors
	 *
	 * This function opens the file name with the input specified flag. If it
	 * fails to open the file, then it prints an error message and RAPIDWRITE_ASSERTs
	 *
	 * @param[in] fileName The name of file to be opened
	 * @param[in] flag The form in which file should be opened (read/write/append..)
	 * @param[in] errStr The error string which must be printed if it fails to open the file
	 * @return FILE* File Handler if file is opened successfully
	 */
	static DEFAULT_VISIBILTY FILE* OpenFileSafely(const char* fileName, const char* flag, const char* errStr);

	/**
	 * @brief Checks if a given file exists
	 *
	 * @param[in] fileName The name of file to be opened
	 * @param[in] errStr The error string which must be printed if it fails to open the file
	 */
	static DEFAULT_VISIBILTY void CheckFileExists(const char* fileName, const char* errStr);

	/**
	 * @brief Dynamically loads a library and checks for errors
	 *
	 * This function loads the library using dlopen with input specified flag and
	 * returns the handler. If it fails, then it prints the error message
	 * determined through dlerror.
	 *
	 * @param[in] libName The name of library which must be loaded
	 * @param[in] flag The flag which must be passed to dlopen to open the library
	 * @return void* The library handler
	 */
	static DEFAULT_VISIBILTY void* OpenLibrarySafely(const char* libName, int flag);

	/**
	 * @brief Dynamically loads a library with default flag and checks for errors
	 *
	 * This function loads the library using dlopen with a default set of flags.
	 * Currently the flags are (RTLD_NOW | RTLD_LOCAL). In internally calls a utility
	 * that checks for error if it fails to load the library
	 *
	 * @param [in] libName The name of library which must be loaded
	 * @return void* The library handler
	 */
	static DEFAULT_VISIBILTY void* OpenLibrarySafely(const char* libName);

	/**
	 * @brief Gets a pointer to a given function inside the dynamic library
	 *
	 * This function gets the pointer to a particular function in the loaded library. If
	 * it is not able to access the pointer, an error message is printed
	 *
	 * @param[in] handle Library handler returned by dlopen, from which the function must be accessed
	 * @param[in] funcName The name of function whose pointer is needed
	 * @param[in] libName Name of library corresponding to the input handler. This is mainly needed for error message
	 * @return void* Pointer to the required function
	 */
	static DEFAULT_VISIBILTY void* GetFuncPointer(void* handle, const char* funcName, const char* libName);

	/**
	 * @brief Opens a library and gets a pointer to the given function
	 *
	 * This utility function opens a library and tries to get the pointer to the
	 * function inside library. It internally implements all the exception handling
	 * if library or function name is invalid
	 *
	 * @param [in] libName Name of library to be loaded
	 * @param [in] funcName Name of function whose pointer needs to be obtained in library
	 * @param [in] noload Specifies whether the library should be loaded or should we get a
	 * 					   reference only when previously loaded version exists
	 * @return void* Pointer to the function
	 */
	static DEFAULT_VISIBILTY void* CheckLibAndFuncLookup(const char* libName, const char* funcName, bool noload);

	/**
	* @brief Gets a pointer to the given function in a library that is loaded
	*
	* This function checks if  the input library was already loaded and gives access
	* to the handle if it had been loaded. Then it looks up the pointer to the
	* required function. If library was not loaded, then it returns with 0.
	* If library is NULL STRING, it gets reference to the function
	* in current application itself.
	*
	* @param[in] libName Name of library
	* @param[in] libFuncName Name of function to be looked up inside library
	* @return VirtAddr Pointer to the required function in the library
	*/
	static DEFAULT_VISIBILTY VirtAddr GetPtrToLibFuncIfLoaded(const char* libName, const char* libFuncName);

	/**
	* @brief Gets the base name of the file from full address
	*
	* @param[in] _full_address Full address of the given file
	* @return std::string Base file name as a string
	*/
	static std::string GetBaseFileName(char * _full_address);

	/**
	 * @brief This function reads a set of strings from an input file and store them in the input array.
	 *
	 * @param [in] fp File from which the strings must be read
	 * @param [in] bufArray A buffer where the strings must be stored
	 * @param[in] sizeBuf Maximum number of strings allowed in bufArray. If the number of strings
	 * in file exceeds sizeBuf, an error is printed
	 * @return int Number of strings read from file
	 */
	static int ReadStringsFromFile(FILE* fp, char* bufArray[], int sizeBuf);

	/**
	* @brief Gets a pointer to the given function in given module handle
	*
	* @param[in] handle Handle to the library which has the function
	* @param[in] funcName Name of function to be looked up inside library
	* @return void * Pointer to the required function in the library
	*/
	static void* GetFuncPointer(void* handle, const char* funcName);

	/**
	 * @brief Dynamically loads a library with given flag 
	 *
	 * This function loads the library using dlopen with a default set of flags.
	 * Currently the flags are (RTLD_NOW | RTLD_LOCAL).	 
	 *
	 * @param [in] libName The name of library which must be loaded
	 * @param[in] flag The flag which must be passed to dlopen to open the library
	 * @return void* The library handler
	 */
	static void* OpenLibrary(const char* libName, int flag);

	/**
	 * @brief Dynamically loads a library with 0 flag with error handling
	 *
	 * @param [in] libName The name of library which must be loaded
	 * @return void* The library handler
	 */
	static void* OpenLibrarySafelyNoLoad(const char* libName);

	/**
	 * @brief Dynamically loads a library with 0 flag
	 *
	 * @param [in] libName The name of library which must be loaded
	 * @return void* The library handler
	 */
	static void* OpenLibraryNoLoadBind(const char* libName);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////						Implemented in MemOperations.cpp						////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/**
	 * @brief This function sets write permission for the page containing the address
	 *
	 * @param [in] _address Input address to get write permission
	 * @param [in] _size Size of the bytes that need to get write permission
	 */
	static DEFAULT_VISIBILTY void SetWritePermission(ADDRESS _address, int _size);

	/**
	 * @brief This function sets execute permission for the page containing the address
	 *
	 * @param [in] _address Input address to get execute permission
	 * @param [in] _size Size of the bytes that need to get execute permission
	 */
	static DEFAULT_VISIBILTY void SetExecutePermission(ADDRESS _address, int _size);

	/**
	 * @brief Allocates memory and copy the string 
	 *
	 * This utility function allocates the memory equal to the size of source
	 * string and copies the data from source string to destination string.
	 *
	 * @param [out] dest Destination buffer
	 * @param [in] src Source string
	 */
	static void AllocAndCopy(char** dest, const char* src);

	/**
	 * @brief Allocates memory and check for errors
	 * 
	 * This function allocated the memory and returns the allocated pointer
	 * If it fails, then it prints the input error message
	 *
	 * @param[in] size Memory to be allocated in bytes
	 * @param[in] errMsg Error message to be printed when it fails to allocated memory of required size
	 * @return A pointer to the allocated memory
	 */
	static DEFAULT_VISIBILTY void* AllocateMemSafely(int size, const char* errMsg);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////						 	Implemented in Conversion.cpp						////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/**
	 * @brief A utility function for converting a string to integer
	 *
	 * @param [in] inStr Input string
	 * @return int String converted to interger form
	 */
	static DEFAULT_VISIBILTY int ConvertStringToInt(std::string inStr);

	/**
	 * @brief A utility function for converting an integer to string
	 *
	 * @param [in] inVal Input integer
	 * @return std::string Integer converted to string form
	 */
	static DEFAULT_VISIBILTY std::string ConvertIntToString(int inVal);

	/**
	 * @brief A utility function for converting a hex to string
	 *
	 * @param [in] inVal Input integer
	 * @return std::string Integer converted to string form
	 */
	static DEFAULT_VISIBILTY std::string ConvertHexToString(int inVal);

	/**
	 * @brief A utility function for converting a byte to string
	 *
	 * @param [in] inVal Input byte
	 * @return std::string Byte converted to string form
	 */	
	static DEFAULT_VISIBILTY std::string ConvertByteToString(byte inVal);

	/**
	 * @brief A utility function for converting a pointer to string
	 *
	 * @param [in] inPtr Input pointer
	 * @return std::string String form of pointer
	 */
	static std::string DEFAULT_VISIBILTY ConvertPtrToString(void* inPtr);

	/**
	 * @brief A utility function for converting a char * pointer to string
	 *
	 * @param [in] inPtr Input pointer
	 * @return std::string String form of the char * pointer
	 */
	static std::string DEFAULT_VISIBILTY ConvertCharPtrToString(char* inPtr);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////							Implemented in Logging.cpp							////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/** @brief Sets the verbosity level and mode 
	 * 
	 * param [in] The verbosity level
	 * param [in] The mode 
	 */
	static DEFAULT_VISIBILTY void SetVerbosityAndMode(int _v_level, int _mode);

	/**
	 * @brief An API to log multiple tyoes of log info for RLBin
	 *
	 * @param [in] str String to be dumped into log file
	 * @param [in] _log_type Type of log file to be used
	 */
	static DEFAULT_VISIBILTY void RLBin_Multi(std::string str, LogType _log_type);

	/**
	 * @brief An API to log the error info for RLBin
	 *
 	 * @param [in] source_file The name of the caller source file 
	 * @param [in] source_file_line The line number in the source file of the caller 
	 * @param [in] errStr Error string to be dumped into error file
	 */
	static DEFAULT_VISIBILTY void RLBin_Error(std::string errStr, std::string source_file, int source_file_line);

	/**
	 * @brief An utility function that prints log file for RLBin
	 *
	 * @param [in] str Input string
	 * @param [in] source_file The name of the caller source file 
	 */
	static DEFAULT_VISIBILTY void RLBin_Log(std::string str, std::string source_file);

	/**
	 * @brief An utility function that prints the module information
	 *
	 * @param [in] str Input string
	 */
	static DEFAULT_VISIBILTY void RLBin_ModLog(std::string str);

	/**
	 * @brief An utility function that prints the thread information
	 *
	 * @param [in] str Input string
	 */
	static DEFAULT_VISIBILTY void RLBin_ThreadLog(std::string str);

	/**
	 * @brief An utility function that prints library calls made by target app
	 *
	 * @param [in] str Input string
	 */
	static DEFAULT_VISIBILTY void RLBin_LibCalls(std::string str);

	/**
	 * @brief A utility function that prints the debug information
	 *
	 * @param [in] source_file The name of the caller source file 
	 * @param [in] source_file_line The line number in the source file of the caller 
	 * @param [in] str Input string
	 */
	static DEFAULT_VISIBILTY void RLBin_Debug(std::string str, std::string source_file, int source_file_line);

	/**
	 * @brief A utility function that prints the trampoline information
	 *
	 * @param [in] str Input string
	 */
	static DEFAULT_VISIBILTY void RLBin_Tram(std::string str);

	/**
	 * @brief A utility function that prints the disassembly information
	 *
	 * @param [in] str Input string
	 */
	static DEFAULT_VISIBILTY void RLBin_Dis(std::string str);

	/**
	 * @brief A utility function that prints CFG of the functions 
	 *
	 * @param [in] str Input string
	 * @param [in] funcname Name of the input function
	 */
	static DEFAULT_VISIBILTY void RLBin_CFG(std::string str, std::string funcname);

	/** @brief A utility function that resets the file used for printing CFG */
	static DEFAULT_VISIBILTY void RLBin_CFG_Reset();

	/**
	 * @brief A utility function that prints Basic Block CFG of the functions
	 *
	 * @param [in] str Input string
	 */
	static DEFAULT_VISIBILTY void RLBin_CFGBB(std::string str);

	/**
	 * @brief A utility function that prints callgraph of the target app
	 *
	 * @param [in] str Input string
	 */
	static DEFAULT_VISIBILTY void RLBin_CALLGRAPH(std::string str);

	/**
	 * @brief A utility function that prints static analysis information
	 *
	 * @param [in] str Input string
	 */
	static DEFAULT_VISIBILTY void RLBin_Static(std::string str);

	/**
	 * @brief A utility function that prints the optimization statistic
	 *
	 * @param [in] str Input string
	 */
	static DEFAULT_VISIBILTY void RLBin_OptStat(std::string str);

	/**
	 * @brief A utility function that prints instrumentation
	 *
	 * @param [in] str Input string
	 */
	static DEFAULT_VISIBILTY void RLBin_Inst(std::string str);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////						 		Implemented in Other.cpp						////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    /**
     * @brief Demangles a C++ mangled function name
     * @param [in] name The mangled name string
     * @return std::string The demangled name
     */
    static std::string demangle(std::string name);

    /**
     * @brief Checks if a function name is mangled
     * @param [in] name The input name
     * @return true if it is mangled
     */
    static DEFAULT_VISIBILTY bool is_mangled(const char* name);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////						 			Variables (Log Files)						////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/** Verbosity Level for Log Files */
	static int Mode;

	/** Verbosity Level for Log Files */
	static int VerbosityLevel;

	/** Number of the analysis folder to dump the log files */
	static int Analysis_Number;

	/** A reference to the logFile, that contains log dumps from RLBin */
	static FILE* logFile;

	/** A reference to the debugFile, that contains debug information from RLBin */
	static FILE* debugFile;

	/** A reference to the errorFile, that contains error logs from RLBin */
	static FILE* errorFile;

	/** A reference to the modLogFile, that contains module information from RLBin */
	static FILE* modLogFile;

	/** A reference to the threadLogFile, that contains thread information from RLBin */
	static FILE* threadLogFile;

	/** A reference to the logFile, that contains library calls made by the target application */
	static FILE* libcallFile;

	/** A reference to the tramFile, that contains trampoline insertion/removal information from RLBin */
	static FILE* tramFile;

	/** A reference to the disassemblyFile, that contains disassembly table information */
	static FILE* disassemblyFile;

	/** A reference to the optStatFile, that contains stats for the optimizations from RLBin */
	static FILE* optStatFile;
	
	/** A reference to the instFile, that contains timer insformation measured by RLBin */
	static FILE* instFile;

	/** A reference to the CFGFile, that contains CFG of the functions discovered by RLBin */
	static FILE* CFGFile;

	/** A reference to the CFGBBFile, that contains Basic Block CFG of the functions discovered by RLBin */	
	static FILE* CFGBBFile;

	/** A reference to the CALLGRAPHFile, that contains call graph of the target application */		
	static FILE* CALLGRAPHFile;

	/** A reference to the StatFile, that contains dump of the static anlaysis done by RLBin */		
	static FILE* StatFile;
};

#endif