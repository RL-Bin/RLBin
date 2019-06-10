/** 
 * @file Conversion.cpp
 * @brief Handles conversion utility functions provided to RL-Bin in RLBinUtils class
 *   
 * This source file contains implementaion of several utility functions which are
 * used to convert different types to eachother.
 */

#include <sstream>
#include <iomanip>

#include "../../include/SubUnits/Utils/defs.h"
#include "../../include/SubUnits/Utils/RLBinUtils.h"

using namespace std;

int RLBinUtils::ConvertStringToInt(std::string inStr)
{
    //Convert this string to Integer
    int value;
    std::stringstream ss(inStr);
    ss >> value;
    return value;
}

std::string RLBinUtils::ConvertIntToString(int inVal)
{
    //create a stringstream
    stringstream ss;

    //add number to the stream
    ss << inVal;

    //return a string with the contents of the stream
    return ss.str();
}

std::string RLBinUtils::ConvertHexToString(int inVal)
{
    //create a stringstream
	stringstream ss;

	ss << "0x" << std::uppercase << std::setfill('0') << std::setw(8) << std::hex << inVal;
	
    //return a string with the contents of the stream
    return ss.str();}

std::string RLBinUtils::ConvertByteToString(byte inVal)
{
    //create a stringstream
    stringstream ss;

    ss << std::uppercase << std::setfill('0') << std::setw(2) << std::hex << (int)inVal;
    
    //return a string with the contents of the stream
    return ss.str();
}

std::string RLBinUtils::ConvertPtrToString(void* inPtr)
{
    stringstream ss;
    ss << inPtr;
    return ss.str();
}

std::string RLBinUtils::ConvertCharPtrToString(char* inPtr)
{
    stringstream ss;
    ss << inPtr;
    return ss.str();
}


