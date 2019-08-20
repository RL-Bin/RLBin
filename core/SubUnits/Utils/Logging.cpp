/** 
 * @file Logging.cpp
 * @brief Handles utility functions to handle logging for RL-Bin in RLBinUtils class
 *
 * This source file contains implementaion of several utility functions which are
 * used to handle logging in a safe manner.
 */

#include <direct.h>

#include "../../include/SubUnits/Utils/defs.h"
#include "../../include/SubUnits/Utils/RLBinUtils.h"

using namespace std;

FILE* RLBinUtils::logFile = 0;
FILE* RLBinUtils::debugFile = 0;
FILE* RLBinUtils::libcallFile = 0;
FILE* RLBinUtils::errorFile = 0;
FILE* RLBinUtils::tramFile = 0;
FILE* RLBinUtils::disassemblyFile = 0;
FILE* RLBinUtils::optStatFile = 0;
FILE* RLBinUtils::timeStatFile = 0;
FILE* RLBinUtils::modLogFile = 0;
FILE* RLBinUtils::threadLogFile = 0;
FILE* RLBinUtils::CFGFile = 0;
FILE* RLBinUtils::CFGBBFile = 0;
FILE* RLBinUtils::CALLGRAPHFile = 0;
FILE* RLBinUtils::StatFile = 0;

void RLBinUtils::RLBin_Multi(std::string str, LogType _log_type)
{
    if(_log_type == T_DEBUG) RLBin_Debug(str, __FILENAME__, __LINE__);
    else if (_log_type == T_LOG) RLBin_Log(str, __FILENAME__);
    else if (_log_type == T_ERROR) RLBin_Error(str, __FILENAME__, __LINE__);
    else if (_log_type == T_DIS) RLBin_Dis(str);
    else if (_log_type == T_TRAM) RLBin_Tram(str);
    else if (_log_type == T_LIBCALL) RLBin_LibCalls(str);
    else if (_log_type == T_OPTSTAT) RLBin_OptStat(str);
    else if (_log_type == T_TIMESTAT) RLBin_TimeStat(str);
    else if (_log_type == T_MODLOG) RLBin_ModLog(str);
    else if (_log_type == T_THREADLOG) RLBin_ThreadLog(str);
    else if (_log_type == T_STATIC) RLBin_Static(str);
    else RLBin_Error("Unexpected Log Type\n", __FILENAME__, __LINE__);
}

void RLBinUtils::RLBin_Error(std::string errStr, std::string source_file, int source_file_line)
{
    // Get the last error code as string
    std::string error_code = std::string();
    DWORD error = GetLastError();
    if (error)
    {
        LPVOID lpMsgBuf;
        DWORD bufLen = FormatMessage(
            FORMAT_MESSAGE_ALLOCATE_BUFFER | 
            FORMAT_MESSAGE_FROM_SYSTEM |
            FORMAT_MESSAGE_IGNORE_INSERTS,
            NULL,
            error,
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
            (LPTSTR) &lpMsgBuf,
            0, NULL );
        if (bufLen)
        {
          LPCSTR lpMsgStr = (LPCSTR)lpMsgBuf;
          std::string result(lpMsgStr, lpMsgStr+bufLen);
          
          LocalFree(lpMsgBuf);

          error_code = result;
        }
    }

    // Now print to file
    printf("RL-Bin has encountered some error and will exit! \nPlease check the error log for details.\n");
    if (!errorFile)
    {
        string fileName = string(BASE_FOLDER) + ConvertIntToString(Analysis_Number) +  string("\\") + BASE_ERROR_FILENAME + string(".txt");
        errorFile = fopen(fileName.c_str(),"a+");
    }
    if (errorFile)
    {        
        std::string tempStr= GetTime();
        tempStr.append("\t");
        tempStr.resize(20, ' ');        
        tempStr.append(source_file);
        tempStr.resize(50, ' ');        
        tempStr.append("\t");
        tempStr.append(ConvertIntToString(source_file_line));
        tempStr.append("\t");
        tempStr.resize(60, ' ');        
        tempStr.append(errStr);
        tempStr.append("\nError Code:\t");
        tempStr.append(error_code);
        fprintf(errorFile, "%s\n", tempStr.c_str());
        fflush(errorFile);
    }

    abort();
}

void RLBinUtils::RLBin_Log(std::string str, std::string source_file)
{
    if (!logFile)
    {
        string fileName = string(BASE_FOLDER) + ConvertIntToString(Analysis_Number) +  string("\\") + BASE_LOG_FILENAME + string(".txt");
        logFile = fopen(fileName.c_str(),"a+");
    }
    if (logFile)
    {
        std::string tempStr= GetTime();
        tempStr.append("\t");
        tempStr.resize(20, ' ');        
        tempStr.append(source_file);
        tempStr.resize(40, ' ');        
        tempStr.append("\t");
        tempStr.append(str);
        fprintf(logFile, "%s\n", tempStr.c_str());
        fflush(logFile);
    }
}

void RLBinUtils::RLBin_ModLog(std::string str)
{
    if (!modLogFile)
    {
        string fileName = string(BASE_FOLDER) + ConvertIntToString(Analysis_Number) +  string("\\") + BASE_MODLOG_FILENAME + string(".txt");
        modLogFile = fopen(fileName.c_str(),"a+");
    }
    if (modLogFile)
    {
        std::string tempStr= "";
        tempStr.append(str);
        fprintf(modLogFile, "%s\n", tempStr.c_str());
        fflush(modLogFile);
    }
}

void RLBinUtils::RLBin_ThreadLog(std::string str)
{
    if (!threadLogFile)
    {
        string fileName = string(BASE_FOLDER) + ConvertIntToString(Analysis_Number) +  string("\\") + BASE_THREADLOG_FILENAME + string(".txt");
        threadLogFile = fopen(fileName.c_str(),"a+");
    }
    if (threadLogFile)
    {
        std::string tempStr= "";
        tempStr.append(str);
        fprintf(threadLogFile, "%s\n", tempStr.c_str());
        fflush(threadLogFile);
    }
}

void RLBinUtils::RLBin_LibCalls(std::string str)
{
    if (!libcallFile)
    {
        string fileName = string(BASE_FOLDER) + ConvertIntToString(Analysis_Number) +  string("\\") + BASE_LIBCALL_FILENAME + string(".txt");
        libcallFile = fopen(fileName.c_str(),"a+");
    }
    if (libcallFile)
    {
        std::string tempStr;
        tempStr.append(str);
        fprintf(libcallFile, "%s\n", tempStr.c_str());
        fflush(libcallFile);
    }
}

void RLBinUtils::RLBin_Debug(std::string str, std::string source_file, int source_file_line)
{
    if (!debugFile)
    {
        string fileName = string(BASE_FOLDER) + ConvertIntToString(Analysis_Number) +  string("\\") + BASE_DEBUG_FILENAME+ string(".txt");
        debugFile = fopen(fileName.c_str(),"a+");
    }
    if (debugFile)
    {
        std::string tempStr;
        tempStr.append(source_file);
        tempStr.resize(30, ' ');        
        tempStr.append(ConvertIntToString(source_file_line));
        tempStr.resize(40, ' ');        
        tempStr.append(str);
        fprintf(debugFile, "%s\n", tempStr.c_str());
        fflush(debugFile);
    }
}

void RLBinUtils::RLBin_Static(std::string str)
{
    if (!StatFile)
    {
        string fileName = string(BASE_FOLDER) + ConvertIntToString(Analysis_Number) +  string("\\") + BASE_STATIC_FILENAME + string(".txt");
        StatFile = fopen(fileName.c_str(), "a+");
    }
    if (StatFile)
    {
        std::string tempStr;
        tempStr.append(str);
        fprintf(StatFile, "%s\n", tempStr.c_str());
        fflush(StatFile);
    }
}

void RLBinUtils::RLBin_Tram(std::string str)
{
    #ifndef RELEASE
    if (!tramFile)
    {
        string fileName = string(BASE_FOLDER) + ConvertIntToString(Analysis_Number) +  string("\\") + BASE_TRAM_FILENAME + string(".txt");
        tramFile = fopen(fileName.c_str(), "a+");
    }
    if (tramFile)
    {
        std::string tempStr;
        tempStr.append(str);
        fprintf(tramFile, "%s\n", tempStr.c_str());
        fflush(tramFile);
    }
    #endif
}

void RLBinUtils::RLBin_Dis(std::string str)
{
    if (!disassemblyFile)
    {
        string fileName = string(BASE_FOLDER) + ConvertIntToString(Analysis_Number) +  string("\\") + BASE_DIS_FILENAME + string(".txt");
        disassemblyFile = fopen(fileName.c_str(), "a+");
    }
    if (disassemblyFile)
    {
        std::string tempStr;
        tempStr.append(str);
        fprintf(disassemblyFile, "%s", tempStr.c_str());
        fflush(disassemblyFile);
    }
}

void RLBinUtils::RLBin_CFG_Reset()
{
    fclose(CFGFile);
    CFGFile = 0;    
}

void RLBinUtils::RLBin_CFG(std::string str, std::string funcname)
{
    const char * FolderName = (string(BASE_FOLDER) + ConvertIntToString(Analysis_Number) + string("\\CFG\\")).c_str();
    _mkdir(FolderName);    
    if (!CFGFile)
    {
        string fileName = string(BASE_FOLDER) + ConvertIntToString(Analysis_Number) + string("\\CFG\\") + BASE_CFG_FILENAME + funcname + string(".gv");
        CFGFile = fopen(fileName.c_str(), "a+");
    }
    if (CFGFile)
    {
        std::string tempStr;
        tempStr.append(str);
        fprintf(CFGFile, "%s", tempStr.c_str());
        fflush(CFGFile);
    }
}

void RLBinUtils::RLBin_CFGBB(std::string str)
{
    if (!CFGBBFile)
    {
        string fileName = string(BASE_FOLDER) + ConvertIntToString(Analysis_Number) +  string("\\") + BASE_CFGBB_FILENAME + string(".gv");
        CFGBBFile = fopen(fileName.c_str(), "a+");
    }
    if (CFGBBFile)
    {
        std::string tempStr;
        tempStr.append(str);
        fprintf(CFGBBFile, "%s", tempStr.c_str());
        fflush(CFGBBFile);
    }
}

void RLBinUtils::RLBin_CALLGRAPH(std::string str)
{
    if (!CALLGRAPHFile)
    {
        string fileName = string(BASE_FOLDER) + ConvertIntToString(Analysis_Number) +  string("\\") + BASE_CALLGRAPH_FILENAME + string(".gv");
        CALLGRAPHFile = fopen(fileName.c_str(), "a+");
    }
    if (CALLGRAPHFile)
    {
        std::string tempStr;
        tempStr.append(str);
        fprintf(CALLGRAPHFile, "%s", tempStr.c_str());
        fflush(CALLGRAPHFile);
    }
}

void RLBinUtils::RLBin_OptStat(std::string str)
{
    if (!optStatFile)
    {
        string fileName = string(BASE_FOLDER) + ConvertIntToString(Analysis_Number) +  string("\\") + BASE_OPTSTAT_FILENAME + string(".txt");
        optStatFile = fopen(fileName.c_str(), "a+");
    }
    if (optStatFile)
    {
        std::string tempStr;
        tempStr.append(str);
        fprintf(optStatFile, "%s\n", tempStr.c_str());
        fflush(optStatFile);
    }
}

void RLBinUtils::RLBin_TimeStat(std::string str)
{
    if (!timeStatFile)
    {
        string fileName = string(BASE_FOLDER) + ConvertIntToString(Analysis_Number) +  string("\\") + BASE_TIMESTAT_FILENAME + string(".txt");
        timeStatFile = fopen(fileName.c_str(), "a+");
    }
    if (timeStatFile)
    {
        std::string tempStr;
        tempStr.append(str);
        fprintf(timeStatFile, "%s\n", tempStr.c_str());
        fflush(timeStatFile);
    }
}