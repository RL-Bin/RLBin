#ifndef _DEFS_H_
#define _DEFS_H_

/** @file defs.h
 * @brief Definitions used in the project 
 *
 * A header file describing several defines used throughout our code
 */

#include <stdint.h>
#include <map>
#include <string>

/////////////////////////////////////////////////////////////////////////////////////////
//////                        Operartion Mode Definitions                           /////
/////////////////////////////////////////////////////////////////////////////////////////

#define ISBASE if((Config::Get()->GetFeatureValue("OptLevel") == 0)&&(Config::Get()->GetFeatureValue("OptMode") != 0))

#define NOTBASE if((Config::Get()->GetFeatureValue("OptLevel") == 1)&&(Config::Get()->GetFeatureValue("OptMode") != 0))

#define ISSTATIC if(Config::Get()->GetFeatureValue("OptMode") == 0)

#define NOTSTATIC if(Config::Get()->GetFeatureValue("OptMode") != 0)

/////////////////////////////////////////////////////////////////////////////////////////
//////             New types defined and used in the code                           /////
/////////////////////////////////////////////////////////////////////////////////////////

/** Defining the typedef for VirtAddr as unsigned int */
typedef long unsigned int VirtAddr;

/** Defining the typedef for each address */
typedef uint32_t  ADDRESS;

/** Defining the typedef for keeping the size information */
typedef uint32_t  SIZE_TYPE;

/** Defining the typedef for each element of the disassembly table */
typedef unsigned char  CELL;

/////////////////////////////////////////////////////////////////////////////////////////
//////                            MAX Size Definitions                              /////
/////////////////////////////////////////////////////////////////////////////////////////

/** Default size of memory allocated for each instrumentation routine */
#define DEFAULT_ROUTINE_SIZE 0x0100

/** Default size of memory allocated for instrumentation routines */
#define SIZE_INSTRUMENATION 0x10000000

/** Size of VIRTADDR in bits */
#define SIZE_VIRTADDR  (BITS_IN_BYTE*sizeof(VirtAddr))

/** A local number which is used to assign the sized of several arrays */
#define SIZE_BUF 128

/** Maximum number of characters in a path */
#define MAX_CHAR_IN_PATH 500

/** Maximum number of arguments for a target inside trampoline */
#define MAX_NUM_ARGS 20

/** Default value for the maximum number of timers that can be used */
#define MAX_TIME_COUNT 10

/** Default value for the maximum number of analysis that can be done */
#define MAX_ANALYSIS 100

/////////////////////////////////////////////////////////////////////////////////////////
//////                         File and Folder Addresses                            /////
/////////////////////////////////////////////////////////////////////////////////////////

/** Source file name that will be printed in logs and error files */
#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)

/** Default value and address of the core dll */
#define CORE_LIB_NAME ".\\bin\\core.dll"

/** Main API function for initiating the RLBin process */
#define START_RLBIN_FUNC "StartRLBin"

/** API function for finalzing the monitoring process inside RLBin */
#define FINALIZE_RLBIN_FUNC "FinalizeRLBin"

#define CURRENT_CONFIG_FILE ".\\config\\config.txt"

/** Base folder for storing the outputs of the program */
#define BASE_FOLDER ".\\analysis\\" 

/** Base file for storing the error outputs from programs */
#define BASE_ERROR_FILENAME "\\RLBin_ErrorLog"

/** Base file for storing the logs from programs */
#define BASE_LOG_FILENAME "\\RLBin_Log"

/** Base file for storing the modules information */
#define BASE_MODLOG_FILENAME "\\RLBin_ModLog"

/** Base file for storing thread information */
#define BASE_THREADLOG_FILENAME "\\RLBin_ThreadLog"

/** Base file for storing the debug logs from programs */
#define BASE_DEBUG_FILENAME "\\RLBin_Debug"

/** Base file for storing the trampoline information */
#define BASE_TRAM_FILENAME "\\RLBin_Tram"

/** Base file for storing the Disassembly Table information */
#define BASE_DIS_FILENAME "\\RLBin_Dis"

/** Base file for storing the library call logs */
#define BASE_LIBCALL_FILENAME "\\RLBin_LibCalls"

/** Base file for storing the Optimization Statistics */
#define BASE_OPTSTAT_FILENAME "\\RLBin_OptStat"

/** Base file for storing the Time Measurements */
#define BASE_TIMESTAT_FILENAME "\\RLBin_TimeStat"

/** Base file for storing each CFG of the function in the target program */
#define BASE_CFG_FILENAME "\\RLBin_CFG"

/** Base file for storing each Basic Block CFG of the function in the target program */
#define BASE_CFGBB_FILENAME "\\RLBin_CFGBB"

/** Base file for storing CallGraph of the target program */
#define BASE_CALLGRAPH_FILENAME "\\RLBin_CALLGRAPH"

/** Base file for storing Static Disassembly log */
#define BASE_STATIC_FILENAME "\\RLBin_StaticAnalyzer"

/////////////////////////////////////////////////////////////////////////////////////////
//////                         Disassembly Table                                    /////
/////////////////////////////////////////////////////////////////////////////////////////

/** Size of disassembly table */
#define SIZE_DIS_TABLE 0x1000000

/** Default value defined for undiscovered memory locations */
#define LOC_UNDISCOVERD      0x00

/** Default value defined for discovered memory locations which are not start of BB */
#define LOC_DISCOVERD        0x01

/** Default value defined for discovered memory locations which are start of BB */
#define LOC_START_OF_BB      0x02

/////////////////////////////////////////////////////////////////////////////////////////
//////                         DEFAULT_VISIBILTY                                    /////
/////////////////////////////////////////////////////////////////////////////////////////

/** Default visibility of the functions in library */
#define DEFAULT_VISIBILTY __declspec(dllexport)

/////////////////////////////////////////////////////////////////////////////////////////
//////                         Defineitions for Inst Class                          /////
/////////////////////////////////////////////////////////////////////////////////////////

/** Opcode for indirect call instruction in x86 */
#define INDIRECT_INST_OPCODE 0xFF

/** Opcode for direct call instruction in x86 */
#define CALL_INST_OPCODE 0xE8

/** Opcode for direct jmp instruction in x86 */
#define JMP_INST_OPCODE 0xE9

/** Opcode for nop instruction in x86 */
#define NOP_INST_OPCODE 0x90

/** Opcode for nop instruction in x86 */
#define PUSHLI_INST_OPCODE 0x68

/** Opcode for trap instruction in x86 */
#define TRAP_INST_OPCODE 0xCC

/////////////////////////////////////////////////////////////////////////////////////////
//////                            List of Exceptions                                /////
/////////////////////////////////////////////////////////////////////////////////////////

#define STILL_ACTIVE                        STATUS_PENDING
#define EXCEPTION_ACCESS_VIOLATION          STATUS_ACCESS_VIOLATION
#define EXCEPTION_DATATYPE_MISALIGNMENT     STATUS_DATATYPE_MISALIGNMENT
#define EXCEPTION_BREAKPOINT                STATUS_BREAKPOINT
#define EXCEPTION_SINGLE_STEP               STATUS_SINGLE_STEP
#define EXCEPTION_ARRAY_BOUNDS_EXCEEDED     STATUS_ARRAY_BOUNDS_EXCEEDED
#define EXCEPTION_FLT_DENORMAL_OPERAND      STATUS_FLOAT_DENORMAL_OPERAND
#define EXCEPTION_FLT_DIVIDE_BY_ZERO        STATUS_FLOAT_DIVIDE_BY_ZERO
#define EXCEPTION_FLT_INEXACT_RESULT        STATUS_FLOAT_INEXACT_RESULT
#define EXCEPTION_FLT_INVALID_OPERATION     STATUS_FLOAT_INVALID_OPERATION
#define EXCEPTION_FLT_OVERFLOW              STATUS_FLOAT_OVERFLOW
#define EXCEPTION_FLT_STACK_CHECK           STATUS_FLOAT_STACK_CHECK
#define EXCEPTION_FLT_UNDERFLOW             STATUS_FLOAT_UNDERFLOW
#define EXCEPTION_INT_DIVIDE_BY_ZERO        STATUS_INTEGER_DIVIDE_BY_ZERO
#define EXCEPTION_INT_OVERFLOW              STATUS_INTEGER_OVERFLOW
#define EXCEPTION_PRIV_INSTRUCTION          STATUS_PRIVILEGED_INSTRUCTION
#define EXCEPTION_IN_PAGE_ERROR             STATUS_IN_PAGE_ERROR
#define EXCEPTION_ILLEGAL_INSTRUCTION       STATUS_ILLEGAL_INSTRUCTION
#define EXCEPTION_NONCONTINUABLE_EXCEPTION  STATUS_NONCONTINUABLE_EXCEPTION
#define EXCEPTION_STACK_OVERFLOW            STATUS_STACK_OVERFLOW
#define EXCEPTION_INVALID_DISPOSITION       STATUS_INVALID_DISPOSITION
#define EXCEPTION_GUARD_PAGE                STATUS_GUARD_PAGE_VIOLATION
#define EXCEPTION_INVALID_HANDLE            STATUS_INVALID_HANDLE
#define EXCEPTION_POSSIBLE_DEADLOCK         STATUS_POSSIBLE_DEADLOCK
#define CONTROL_C_EXIT                      STATUS_CONTROL_C_EXIT

/////////////////////////////////////////////////////////////////////////////////////////
//////                       List of Section Header Constants                       /////
/////////////////////////////////////////////////////////////////////////////////////////
#define SECTION__WRITE_PERM  0x80
#define SECTION__READ_PERM  0x40
#define SECTION__EXE_PERM  0x20

#define SECTION__CONTAIN_CODE  0x20
#define SECTION__CONTAIN_IDATA  0x40
#define SECTION__CONTAIN_UDATA  0x80

/////////////////////////////////////////////////////////////////////////////////////////
//////                Enums for Logging and Instrumentation Types                   /////
/////////////////////////////////////////////////////////////////////////////////////////

/** Defining the typedef for different logging types */
typedef enum LogType
{
    T_DEBUG,
    T_LOG,
    T_ERROR,
    T_DIS,
    T_TRAM,
    T_LIBCALL,
    T_OPTSTAT,
    T_MODLOG,
    T_THREADLOG,
    T_TIMESTAT,
    T_STATIC
} LogType;

/** Defining the typedef for different instuction types */
typedef enum InstType
{
    MOVEBI,
    MOVELI,
    JMP,
    PUSHLI,
    OTHER
} InstType;

/** Defining the typedef for different instruction routine types */
typedef enum InstRoutineType
{
    INDJMPROUTINE,
    INDCALLROUTINE5,
    INDCALLROUTINE6,
    INDCALLROUTINE7,
    OTHERROUTINE
} InstRoutineType;

/** Defining the typedef for different optimization instruction routine types */
typedef enum OptInstRoutineType
{
    RETROUTINE,
    GENERALOPTROUTINE,
    OPTOTHERROUTINE
} OptInstRoutineType;

#endif
