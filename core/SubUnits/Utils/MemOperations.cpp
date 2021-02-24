/** 
 * @file MemOperations.cpp
 * @brief Handles utility functions to handle memory operations for RL-Bin in RLBinUtils class
 *
 * This source file contains implementaion of several utility functions which are
 * used to handle memory operations in a safe manner.
 */

#include "../../include/SubUnits/Utils/defs.h"
#include "../../include/SubUnits/Utils/RLBinUtils.h"

using namespace std;

void RLBinUtils::AllocAndCopy(char** dest, const char* src)
{
    *dest = (char*) AllocateMemSafely(SIZE_BUF,"Arg Alloc");
    strcpy(*dest,src);
}

void* RLBinUtils::AllocateMemSafely(int sizeInBytes,  const char* errStr)
{
    //Allocate memory of required size
    void* allocMem = malloc(sizeInBytes);

    //Error check
    if (allocMem==NULL)
    {
        std::string tempStr = "Failed to allocate memory for ";
        tempStr.append(errStr);
        RLBin_Error(tempStr, __FILENAME__, __LINE__);
    }
    return allocMem;
}

void RLBinUtils::SetWritePermission(ADDRESS _address, int _size)
{
    DWORD OldProtection;
    if (!VirtualProtect((LPVOID)_address, _size, PAGE_EXECUTE_READWRITE, &OldProtection))
    {
        RLBin_Error("Cannot set write permission at address :" + ConvertHexToString(_address) + "\n", __FILENAME__, __LINE__);
    }
}

void RLBinUtils::SetExecutePermission(ADDRESS _address, int _size)
{
    DWORD OldProtection;
    if (!VirtualProtect((LPVOID)_address, _size, PAGE_EXECUTE_READWRITE, &OldProtection))
    {
        RLBin_Error("Cannot set execute permission at address :" + ConvertHexToString(_address) + "\n", __FILENAME__, __LINE__);
    }
}