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

	IMU::Create();
	IMU::Get()->Initialize();
	IMU::Get()->CreateInstRoutineRet();

	Disassembler::Get()->PrintNInsts(IMU::Get()->RetRoutine, T_TRAM, 17);

	counter = 0;

	return;
}

void CU::Finalize(void) 
{
	TMU::Get()->RemoveAllTrampolines();
	Disassembler::Get()->PrintDisassembly();
	return;
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
		RLBinUtils::RLBin_Debug("STATUS    :    DF", __FILENAME__, __LINE__);
	}
	else if(Disassembler::Get()->IsInstDirectJump(add))
	{
		RLBinUtils::RLBin_Debug("STATUS    :    DJ0", __FILENAME__, __LINE__);
		HandleNewDJ(add);
		RLBinUtils::RLBin_Debug("STATUS    :    DF", __FILENAME__, __LINE__);
	}
	else if(Disassembler::Get()->IsInstIndirectCall(add))
	{
		RLBinUtils::RLBin_Debug("STATUS    :    IC0", __FILENAME__, __LINE__);		
		ADDRESS call_address;
		Disassembler::Get()->GetIndirectCTIDest(add, &call_address, p->ContextRecord);

		Inst current;
		Disassembler::Get()->GetOneInst(add, &current);
		ADDRESS next_inst = add + current.size;

		RLBinUtils::RLBin_Debug("Call Target  " + RLBinUtils::ConvertHexToString(call_address), __FILENAME__, __LINE__);
		RLBinUtils::RLBin_Debug("Next Address " + RLBinUtils::ConvertHexToString(next_inst), __FILENAME__, __LINE__);

		// Add next to pre type 2 if not already type 2
		RLBinUtils::RLBin_Debug("STATUS    :    IC1", __FILENAME__, __LINE__);
		HandleNewICJ(add, call_address, next_inst);		

		RLBinUtils::RLBin_Debug("STATUS    :    IF", __FILENAME__, __LINE__);
	}
	else if(Disassembler::Get()->IsInstIndirectJump(add))
	{
		RLBinUtils::RLBin_Debug("STATUS    :    IJ0", __FILENAME__, __LINE__);
		ADDRESS jump_address;
		Disassembler::Get()->GetIndirectCTIDest(add, &jump_address, p->ContextRecord);
		ADDRESS next_inst = *((ADDRESS *)p->ContextRecord->Esp);
		RLBinUtils::RLBin_Debug("Jump Target  " + RLBinUtils::ConvertHexToString(jump_address), __FILENAME__, __LINE__);
		RLBinUtils::RLBin_Debug("Next Address " + RLBinUtils::ConvertHexToString(next_inst), __FILENAME__, __LINE__);
		HandleNewICJ(add, jump_address, next_inst);						
		RLBinUtils::RLBin_Debug("STATUS    :    IF", __FILENAME__, __LINE__);
	}
	else if(Disassembler::Get()->IsInstRet(add))
	{
		RLBinUtils::RLBin_Debug("STATUS    :    R0", __FILENAME__, __LINE__);
		
		ADDRESS return_address;
		Disassembler::Get()->GetIndirectCTIDest(add, &return_address, p->ContextRecord);
		RLBinUtils::RLBin_Debug("Ret Target  " + RLBinUtils::ConvertHexToString(return_address), __FILENAME__, __LINE__);
		HandleNewR(add, return_address);
		RLBinUtils::RLBin_Debug("STATUS    :    RF", __FILENAME__, __LINE__);

		if(*(byte *)add == 0xc3)
		{
			TMU::Get()->InsertTrampoline(add);
			p->ContextRecord->Eip = return_address;	
			p->ContextRecord->Esp += 4;		
		}
	}	
	else
	{
		RLBinUtils::RLBin_Debug("STATUS    :    NC0", __FILENAME__, __LINE__);				
		HandleNewNC(add);
		RLBinUtils::RLBin_Debug("STATUS    :    NF", __FILENAME__, __LINE__);
	}
	return;
}

void CU::HandleMissedCheck(PEXCEPTION_POINTERS p)
{
	RLBinUtils::RLBin_Debug("STATUS____:____R0", __FILENAME__, __LINE__);
	ADDRESS return_address = *(((ADDRESS *) p->ContextRecord->Esp));	

	RLBinUtils::RLBin_Debug(RLBinUtils::ConvertHexToString(return_address), __FILENAME__, __LINE__);
	
	// Check External Dest
	RLBinUtils::RLBin_Debug("STATUS____:____R1", __FILENAME__, __LINE__);

	if(!Modules::Get()->IsInsideMainCode(return_address))
	{
	}
	else
	{
		// Check return address discovered
		RLBinUtils::RLBin_Debug("STATUS____:____R2", __FILENAME__, __LINE__);
		if(DisTable::Get()->GetEntry(return_address) == LOC_UNDISCOVERD)
		{
			// Put trap to be discovered
			TMU::Get()->InsertTrampoline(return_address);
			RLBinUtils::RLBin_Debug("STATUS____:____R3", __FILENAME__, __LINE__);
		}
	}


	p->ContextRecord->Eip = return_address;	
	p->ContextRecord->Esp += 4;		

	return;
}