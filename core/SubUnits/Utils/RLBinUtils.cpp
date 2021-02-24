/** 
 * @file RLBinUtils.cpp
 * @brief Handles main utility functions for RL-Bin in RLBinUtils class
 *
 * This source file contains implementaion of several utility functions which are
 * used for different purposes in RL-Bin.
 */

#include "../../include/SubUnits/Utils/defs.h"
#include "../../include/SubUnits/Utils/RLBinUtils.h"

using namespace std;

int RLBinUtils::Analysis_Number = 0;

void RLBinUtils::Init()
{
    const char * pathname = BASE_FOLDER;
    CreateDirectory(pathname, NULL);
    int analysis_number = 1;
    char analysis_pathname[256];
    DWORD ftyp;
    for(;analysis_number <= MAX_ANALYSIS; analysis_number++)
    {
        strcpy(analysis_pathname, BASE_FOLDER);
        strcat(analysis_pathname, ConvertIntToString(analysis_number).c_str());   
        ftyp = GetFileAttributesA(analysis_pathname);
        if (ftyp == INVALID_FILE_ATTRIBUTES) 
            break;
    }
    Analysis_Number = analysis_number;
    CreateDirectory(analysis_pathname, NULL);
}

void RLBinUtils::ReadAnalysisNumber()
{
    int analysis_number = 1;
    char analysis_pathname[256];
    DWORD ftyp;
    for(;analysis_number <= MAX_ANALYSIS; analysis_number++)
    {
        strcpy(analysis_pathname, BASE_FOLDER);
        strcat(analysis_pathname, ConvertIntToString(analysis_number).c_str());   
        ftyp = GetFileAttributesA(analysis_pathname);
        if (ftyp == INVALID_FILE_ATTRIBUTES) 
            break;
    }
    Analysis_Number = analysis_number-1;
}

std::string RLBinUtils::GetTime(void)
{
    time_t rawtime;
    time(&rawtime);
    struct tm* timeinfo = localtime(&rawtime);

    char buffer [80];
    
    strftime (buffer,80,"%H:%M:%S.",timeinfo);
    
    std::string tempStr(buffer);
    //asctime(timeinfo);
    tempStr = tempStr.substr(0,tempStr.size()-1);
    tempStr.append(" ");
    return tempStr;
}


std::string RLBinUtils::AppendStrings(int n,...)
{
    va_list v1;
    va_start(v1,n);
    std::string retval = va_arg(v1,char*);
    for (int i=1; i<n; i++)
    {
        retval.append(va_arg(v1,char*));
        retval.append(" ");
    }
    return retval;
}

bool RLBinUtils::isCurrentApp(const char* libName)
{
    string appName = string(GetApplicationName());
    if(strcmp(appName.c_str(), libName))
       return false;
    else
       return true;
}

std::string RLBinUtils::GetSelfPath(void)
{
    int len;
    char buff[MAX_PATH];
    len = GetModuleFileNameA(NULL, buff, sizeof(buff) - 1);
    if (len != 0)
    {
        buff[len] = '\0';
        std::string temp = buff;
        return temp;
    }
    else
        RLBin_Error("Correct full path not found for this application \n", __FILENAME__, __LINE__);
    return std::string("");
}

std::string RLBinUtils::GetApplicationName(void)
{
    char appname[MAX_PATH];
    int len = GetModuleFileNameA(NULL, appname,MAX_PATH - 1);
    std::string tempApp = appname;
    tempApp = tempApp.substr(tempApp.rfind("\\") + 1);
    tempApp = tempApp.substr(0, tempApp.find("."));
    return tempApp;
}

std::string RLBinUtils::GetLastErrorString(void)
{
    std::string retval;
    int errNo = GetLastError();
    retval = " Error No: ";
    retval += ConvertIntToString(errNo);
    return retval;
}
