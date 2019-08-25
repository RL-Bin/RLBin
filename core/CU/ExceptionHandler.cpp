/**
 * @file ExceptionHandler.cpp
 * @brief This file contains the implementation of exception handler
 */

#include <stdlib.h>
#include <Windows.h>

#include "..\include\SubUnits\Utils\defs.h"
#include "..\include\SubUnits\Utils\RLBinUtils.h"

#include "..\include\CU\CU.h"
#include "..\include\IMU\IMU.h"
#include "..\include\SubUnits\Modules\Modules.h"
#include "..\include\DataStructs\DisTable\DisTable.h"

/** @brief global variable base of module */
ADDRESS ModBase;

/** @brief global variable end of module */
ADDRESS ModEnd;

/** @brief global variable Distable Offset */
ADDRESS DisOffset;

/** @brief global variable Instrumentation Address */
ADDRESS RetRoutine;

void InitGlobals()
{
	ModBase = Modules::Get()->GetMainModule()->base_address;
	ModEnd = ModBase + Modules::Get()->GetMainModule()->module_size;
	DisOffset = DisTable::Get()->GetOffset();
	RetRoutine = IMU::Get()->RetRoutine;
	return;
}


LONG WINAPI RLBinExceptionHandler(PEXCEPTION_POINTERS p)
{
	ADDRESS exception_address = (ADDRESS)p->ExceptionRecord->ExceptionAddress;

	/** Optimized Begin */
	if((exception_address >= ModBase) && (exception_address <=ModEnd))
	{
		if(*((byte *)(exception_address+DisOffset)))
		{
			p->ContextRecord->Eip = RetRoutine;	
			return EXCEPTION_CONTINUE_EXECUTION;
		}

	}
	/** Optimized End */

	CU::Get()->counter++;
	RLBinUtils::RLBin_Debug("Exception Handler Called times #" + RLBinUtils::ConvertIntToString(CU::Get()->counter), __FILENAME__, __LINE__);

	DWORD e_code  = p->ExceptionRecord->ExceptionCode;
	if (e_code == EXCEPTION_BREAKPOINT)
	{
		RLBinUtils::RLBin_Debug(RLBinUtils::ConvertHexToString(p->ContextRecord->Eip), __FILENAME__, __LINE__);
		// We may face 3 Possibilities

		if(Modules::Get()->IsInsideMainCode(exception_address))
		{
			// 1. New code is being discovered
			if(DisTable::Get()->GetEntry(exception_address) == LOC_UNDISCOVERD)
			{
				CU::Get()->HandleNewCode(p);
				return EXCEPTION_CONTINUE_EXECUTION;
			}
			// 2. It's a recurring check for indirect CTI
			else
			{
				RLBinUtils::RLBin_Debug("Going to Ret Routine ", __FILENAME__, __LINE__);
				p->ContextRecord->Eip = IMU::Get()->RetRoutine;	
				return EXCEPTION_CONTINUE_EXECUTION;			
			}
		}
		// 3. An instrumentation routine needs to change
		else
		{
			CU::Get()->HandleMissedCheck(p);
			//RLBinUtils::RLBin_Error("Exception Coming from outside, Not Implemented! " + RLBinUtils::ConvertHexToString(exception_address), __FILENAME__, __LINE__);	
			return EXCEPTION_CONTINUE_EXECUTION;
		}

	}
	else if (e_code == EXCEPTION_ACCESS_VIOLATION)
	{
		RLBinUtils::RLBin_Error("EXCEPTION_ACCESS_VIOLATION  at address: \t" + RLBinUtils::ConvertHexToString(exception_address), __FILENAME__, __LINE__);
	}
	else if (e_code == STILL_ACTIVE)
	{
		RLBinUtils::RLBin_Error("STILL_ACTIVE at address: \t" + RLBinUtils::ConvertHexToString(exception_address), __FILENAME__, __LINE__);
	}
	else if (e_code == EXCEPTION_DATATYPE_MISALIGNMENT)
	{
		RLBinUtils::RLBin_Error("EXCEPTION_DATATYPE_MISALIGNMENT at address: \t" + RLBinUtils::ConvertHexToString(exception_address), __FILENAME__, __LINE__);
	}
	else if (e_code == EXCEPTION_SINGLE_STEP)
	{
		RLBinUtils::RLBin_Error("EXCEPTION_SINGLE_STEP at address: \t" + RLBinUtils::ConvertHexToString(exception_address), __FILENAME__, __LINE__);
	}
	else if (e_code == EXCEPTION_ARRAY_BOUNDS_EXCEEDED)
	{
		RLBinUtils::RLBin_Error("EXCEPTION_ARRAY_BOUNDS_EXCEEDED at address: \t" + RLBinUtils::ConvertHexToString(exception_address), __FILENAME__, __LINE__);
	}
	else if (e_code == EXCEPTION_FLT_DENORMAL_OPERAND)
	{
		RLBinUtils::RLBin_Error("EXCEPTION_FLT_DENORMAL_OPERAND at address: \t" + RLBinUtils::ConvertHexToString(exception_address), __FILENAME__, __LINE__);
	}
	else if (e_code == EXCEPTION_FLT_DIVIDE_BY_ZERO)
	{
		RLBinUtils::RLBin_Error("EXCEPTION_FLT_DIVIDE_BY_ZERO at address: \t" + RLBinUtils::ConvertHexToString(exception_address), __FILENAME__, __LINE__);
	}
	else if (e_code == EXCEPTION_FLT_INEXACT_RESULT)
	{
		RLBinUtils::RLBin_Error("EXCEPTION_FLT_INEXACT_RESULT at address: \t" + RLBinUtils::ConvertHexToString(exception_address), __FILENAME__, __LINE__);
	}
	else if (e_code == EXCEPTION_FLT_INVALID_OPERATION)
	{
		RLBinUtils::RLBin_Error("EXCEPTION_FLT_INVALID_OPERATION at address: \t" + RLBinUtils::ConvertHexToString(exception_address), __FILENAME__, __LINE__);
	}
	else if (e_code == EXCEPTION_FLT_OVERFLOW)
	{
		RLBinUtils::RLBin_Error("EXCEPTION_FLT_OVERFLOW at address: \t" + RLBinUtils::ConvertHexToString(exception_address), __FILENAME__, __LINE__);
	}
	else if (e_code == EXCEPTION_FLT_STACK_CHECK)
	{
		RLBinUtils::RLBin_Error("EXCEPTION_FLT_STACK_CHECK at address: \t" + RLBinUtils::ConvertHexToString(exception_address), __FILENAME__, __LINE__);
	}
	else if (e_code == EXCEPTION_FLT_UNDERFLOW)
	{
		RLBinUtils::RLBin_Error("EXCEPTION_FLT_UNDERFLOW at address: \t" + RLBinUtils::ConvertHexToString(exception_address), __FILENAME__, __LINE__);
	}
	else if (e_code == EXCEPTION_INT_DIVIDE_BY_ZERO)
	{
		RLBinUtils::RLBin_Error("EXCEPTION_INT_DIVIDE_BY_ZERO at address: \t" + RLBinUtils::ConvertHexToString(exception_address), __FILENAME__, __LINE__);
	}
	else if (e_code == EXCEPTION_INT_OVERFLOW)
	{
		RLBinUtils::RLBin_Error("EXCEPTION_INT_OVERFLOW at address: \t" + RLBinUtils::ConvertHexToString(exception_address), __FILENAME__, __LINE__);
	}
	else if (e_code == EXCEPTION_PRIV_INSTRUCTION)
	{
		RLBinUtils::RLBin_Error("EXCEPTION_PRIV_INSTRUCTION at address: \t" + RLBinUtils::ConvertHexToString(exception_address), __FILENAME__, __LINE__);
	}
	else if (e_code == EXCEPTION_IN_PAGE_ERROR)
	{
		RLBinUtils::RLBin_Error("EXCEPTION_IN_PAGE_ERROR at address: \t" + RLBinUtils::ConvertHexToString(exception_address), __FILENAME__, __LINE__);
	}
	else if (e_code == EXCEPTION_ILLEGAL_INSTRUCTION)
	{
		RLBinUtils::RLBin_Error("EXCEPTION_ILLEGAL_INSTRUCTION at address: \t" + RLBinUtils::ConvertHexToString(exception_address), __FILENAME__, __LINE__);
	}
	else if (e_code == EXCEPTION_NONCONTINUABLE_EXCEPTION)
	{
		RLBinUtils::RLBin_Error("EXCEPTION_NONCONTINUABLE_EXCEPTION at address: \t" + RLBinUtils::ConvertHexToString(exception_address), __FILENAME__, __LINE__);
	}
	else if (e_code == EXCEPTION_STACK_OVERFLOW)
	{
		RLBinUtils::RLBin_Error("EXCEPTION_STACK_OVERFLOW at address: \t" + RLBinUtils::ConvertHexToString(exception_address), __FILENAME__, __LINE__);
	}
	else if (e_code == EXCEPTION_INVALID_DISPOSITION)
	{
		RLBinUtils::RLBin_Error("EXCEPTION_INVALID_DISPOSITION at address: \t" + RLBinUtils::ConvertHexToString(exception_address), __FILENAME__, __LINE__);
	}
	else if (e_code == EXCEPTION_GUARD_PAGE)
	{
		RLBinUtils::RLBin_Error("EXCEPTION_GUARD_PAGE at address: \t" + RLBinUtils::ConvertHexToString(exception_address), __FILENAME__, __LINE__);
	}
	else if (e_code == EXCEPTION_INVALID_HANDLE)
	{
		RLBinUtils::RLBin_Error("EXCEPTION_INVALID_HANDLE at address: \t" + RLBinUtils::ConvertHexToString(exception_address), __FILENAME__, __LINE__);
	}
	else if (e_code == CONTROL_C_EXIT)
	{
		RLBinUtils::RLBin_Error("CONTROL_C_EXIT at address: \t" + RLBinUtils::ConvertHexToString(exception_address), __FILENAME__, __LINE__);
	}
	else
	{
		RLBinUtils::RLBin_Error("Unknow exception at address: \t" + RLBinUtils::ConvertHexToString(exception_address), __FILENAME__, __LINE__);
	}
	return EXCEPTION_CONTINUE_EXECUTION;
}
