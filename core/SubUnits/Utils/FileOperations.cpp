/** 
 * @file FileOperations.cpp
 * @brief Handles utility functions to handle file operations for RL-Bin in RLBinUtils class
 *   
 * This source file contains implementaion of several utility functions which are
 * used to handle file operations and loading libraries and functions in a safe manner.
 */
#include <iostream>
#include "../../include/SubUnits/Utils/defs.h"
#include "../../include/SubUnits/Utils/RLBinUtils.h"

using namespace std;

std::string RLBinUtils::GetBaseFileName(char *_full_address)
{
    char name[MAX_PATH];
    int last_index = 0;
    int null_index = 0;
    for(int j=0; j<MAX_PATH; j++)
    {
        if(_full_address[j] == '\\') last_index = j;
        if(_full_address[j] == '\0')
        {
            null_index = j;
            break;
        }                   
    }
    for(int j=last_index; j<null_index; j++)
    {
        name[j-last_index] = _full_address[j+1];
    }
    std::string file_name(name);
    return file_name;
}

FILE* RLBinUtils::OpenFileSafely(const char* fileName, const char* flag, const char* errStr)
{
    FILE* f = fopen(fileName,flag);

    //Error check
    if (f==NULL)
    {
        string tempStr = AppendStrings(3,errStr," Name:",fileName);
		RLBinUtils::RLBin_Error(tempStr, __FILENAME__, __LINE__);
    }
    return f;
}

void RLBinUtils::CheckFileExists(const char* fileName, const char* errStr)
{
	FILE *pfile;
	if (!( fopen_s(&pfile, fileName, "r")))
		fclose(pfile);
	else
	{
		std::cout << "File not found : " << fileName << std::endl;
		string tempStr = AppendStrings(3, errStr, "FileName not found -> Name: ",fileName);
		RLBinUtils::RLBin_Error(tempStr, __FILENAME__, __LINE__);
	}
}

void* RLBinUtils::OpenLibrarySafely(const char* libName, int flag)
{
    RLBin_Debug("Getting handle to library " + string(libName), __FILENAME__, __LINE__);
	void* handle = OpenLibrary(libName,flag);
	if (!handle)
	{
		string errStr = "Error while loading library: " + string(libName);
		errStr += GetLastErrorString();
		RLBin_Error(errStr, __FILENAME__, __LINE__);
	}
	return handle;
}

void* RLBinUtils::GetFuncPointer(void* handle, const char* funcName, const char* libName)
{
	void* symFunc;
	if (handle == NULL)
	{
		RLBin_Error("Cannot get handle to function " + string(funcName) + " in library " + string (libName), __FILENAME__, __LINE__);
	}
	RLBin_Debug("Getting handle to function " + string(funcName) + " in library " + string (libName), __FILENAME__, __LINE__);

	//Get hold of the function in this library
	symFunc = GetFuncPointer(handle, funcName);

	if (symFunc == NULL)
	{
		std::string errStr = AppendStrings(4, "Failed to get Function: ", funcName, " from library: ", libName);
		errStr += GetLastErrorString();
		RLBin_Error(errStr, __FILENAME__, __LINE__);
		return NULL;
	}
	return symFunc;
}

void* RLBinUtils::GetFuncPointer(void*handle, const char* funcName)
{
    //Get hold of the function in this library
    void *symFunc = GetProcAddress((HMODULE)handle, funcName);
    return symFunc;
}

void* RLBinUtils::CheckLibAndFuncLookup(const char* libName, const char* funcName, bool noload)
{
	//Check whether we are able to load the library
	void* handle;

	const char* tempName = libName;
	if (isCurrentApp(libName))
	{
		tempName = NULL;
	}

	//if noload flag is specifed, then we should not load the library
	if (noload)
	{
		//Open the library with default flags
		handle = OpenLibrarySafelyNoLoad(tempName);
	}
	else
	{
		//Otherwise just get to default library open
		handle = OpenLibrarySafely(tempName);
	}

	//Check whether we are able to get function pointer or not, this function
	//internally raises exception if not found
	void* pFunc = GetFuncPointer(handle, funcName, libName);

	return pFunc;
}

VirtAddr RLBinUtils::GetPtrToLibFuncIfLoaded(const char* libName, const char* libFuncName)
{
	const char* tempName = libName;

	//NULLSTRING in input implies we want to load from current application itself
	if (isCurrentApp(libName))
	{
		tempName = NULL;
	}

	void* handle = OpenLibraryNoLoadBind(tempName);

	//Get access to our required library only if it is already loaded
	if (handle == NULL)
	{
		RLBin_Error("Library: " + string(libName) + " not yet loaded\n", __FILENAME__, __LINE__);
		return 0;
	}

	void* pFunc = NULL;

	//Get access to the required function in this library
	*(void **)(&pFunc) = RLBinUtils::GetFuncPointer(handle, libFuncName, libName);

	VirtAddr funcPtr = (VirtAddr)(pFunc);
	return funcPtr;
}

int RLBinUtils::ReadStringsFromFile(FILE* fp, char* bufArray[], int sizeBuf)
{
    char tempbuf[SIZE_BUF];
    int retval=0;

    //Loop over the input file and store each target in the targetList array.
    while (fscanf(fp,"%s",tempbuf)!=EOF)
    {
        char* tempval = (char*)AllocateMemSafely(sizeof(char)*SIZE_BUF,"Arg Alloc");
        RLBin_Debug("Read: " + string(tempbuf) + string("\n"), __FILENAME__, __LINE__);
        strcpy(tempval, tempbuf);
        bufArray[retval]=tempval;
        retval++;
        if (retval > sizeBuf)
        {
            string tempStr = "Trying to read more strings from input than allowed";
            RLBin_Error(tempStr, __FILENAME__, __LINE__);
        }
    }
    return retval;
}

void* RLBinUtils::OpenLibraryNoLoadBind(const char* libName)
{
    return OpenLibrary(libName,0);
}

void* RLBinUtils::OpenLibrarySafely(const char* libName)
{
    return OpenLibrarySafely(libName, 0);
}

void* RLBinUtils::OpenLibrarySafelyNoLoad(const char* libName)
{
    return OpenLibrarySafely(libName);
}

void* RLBinUtils::OpenLibrary(const char* libName, int flag)
{
    void* handle = LoadLibraryA(libName);
    return handle;
}
