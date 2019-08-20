/**
 * @file CU.cpp
 * @brief Defines the body of functions in CU class.
 */

#include "..\include\CU\CU.h"


#include "..\include\TMU\TMU.h"
#include "..\include\IMU\IMU.h"

#include "..\include\SubUnits\Modules\Modules.h"
#include "..\include\DataStructs\DisTable\DisTable.h"
#include "..\include\SubUnits\Disassembler\Disassembler.h"

// inititalizing the only instace of class 
CU* CU::s_instance = NULL;

CU* CU::Create(void) 
{
	if (s_instance != NULL)
	{
		RLBinUtils::RLBin_Error("An instance of CU exists", __FILENAME__, __LINE__);
		return NULL;
	}
	s_instance = new CU();
	return s_instance;
}

CU* CU::Get(void) 
{
	if (s_instance == NULL)
	{
		RLBinUtils::RLBin_Error("CU is not initialized yet!", __FILENAME__, __LINE__);
		return NULL;
	}
	return s_instance;
}

void CU::Initialize(void) 
{
	Disassembler::Create();

	Modules::Create();
	Modules::Get()->Initialize();
	Modules::Get()->PrintModulesShort();

	DisTable::Create();
	DisTable::Get()->Initialize(Modules::Get()->GetMainModule()->module_size);

	TMU::Create();
	TMU::Get()->Initialize();
}

void CU::Finalize(void) 
{
	Disassembler::Get()->PrintDisassembly();
}

void CU::HandleNewCode(PEXCEPTION_POINTERS p)
{
	// Remove Current Tramp 
	// STATUS    :    1
	ADDRESS add = (ADDRESS)p->ExceptionRecord->ExceptionAddress;
	TMU::Get()->RemoveTrampoline(add);	

	Disassembler::Get()->PrintInst(add, T_DEBUG);
	RLBinUtils::RLBin_Debug("STATUS    :    1", __FILENAME__, __LINE__);

	//Within Function
	RLBinUtils::RLBin_Debug("STATUS    :    2", __FILENAME__, __LINE__);

	//Analyze  Function Must be pre type 2
	RLBinUtils::RLBin_Debug("STATUS    :    31", __FILENAME__, __LINE__);

	// Set DisTable,      Dis, type 1 or 2
	RLBinUtils::RLBin_Debug("STATUS    :    4", __FILENAME__, __LINE__);

	DisTable::Get()->SetEntry(add, LOC_DISCOVERD);

	// Check inst type
	RLBinUtils::RLBin_Debug("STATUS    :    5", __FILENAME__, __LINE__);

	if(Disassembler::Get()->IsInstDirectCall(add))
	{
		RLBinUtils::RLBin_Debug("STATUS    :    DC0", __FILENAME__, __LINE__);
		HandleNewDC(add);
	}
	else if(Disassembler::Get()->IsInstDirectJump(add))
	{
		RLBinUtils::RLBin_Debug("STATUS    :    DJ0", __FILENAME__, __LINE__);
		HandleNewDJ(add);
	}
	else if(Disassembler::Get()->IsInstIndirectCall(add))
	{
		RLBinUtils::RLBin_Debug("STATUS    :    IC0", __FILENAME__, __LINE__);		
	}
	else if(Disassembler::Get()->IsInstIndirectJump(add))
	{
		RLBinUtils::RLBin_Debug("STATUS    :    IJ0", __FILENAME__, __LINE__);		
	}
	else if(Disassembler::Get()->IsInstRet(add))
	{
		RLBinUtils::RLBin_Debug("STATUS    :    R0", __FILENAME__, __LINE__);		
	}	
	else
	{
		RLBinUtils::RLBin_Debug("STATUS    :    NC0", __FILENAME__, __LINE__);				
		HandleNewNC(add);
	}

	RLBinUtils::RLBin_Debug("STATUS    :    DF", __FILENAME__, __LINE__);
}
