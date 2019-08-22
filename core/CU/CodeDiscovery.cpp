/**
 * @file CodeDiscovery.cpp
 * @brief Defines the functions used to handle discovery of new code.
 */

#include "..\include\CU\CU.h"


#include "..\include\TMU\TMU.h"
#include "..\include\IMU\IMU.h"

#include "..\include\SubUnits\Modules\Modules.h"
#include "..\include\DataStructs\DisTable\DisTable.h"
#include "..\include\SubUnits\Disassembler\Disassembler.h"

void CU::HandleNewDC(ADDRESS _address)
{
	// Add next to pretype 2
	RLBinUtils::RLBin_Debug("STATUS    :    DC1", __FILENAME__, __LINE__);

	// Check Call Dest Discovered
	RLBinUtils::RLBin_Debug("STATUS    :    DC2", __FILENAME__, __LINE__);

	ADDRESS call_dest;
	Disassembler::Get()->GetDirectCTIDest(_address, &call_dest);
	if(DisTable::Get()->GetEntry(call_dest) == LOC_UNDISCOVERD)
	{
		// Check Call Dest Middle of function
		RLBinUtils::RLBin_Debug("STATUS    :    DC3", __FILENAME__, __LINE__);

		// Register function
		RLBinUtils::RLBin_Debug("STATUS    :    DC4", __FILENAME__, __LINE__);

		// Put trap to be discovered
		TMU::Get()->InsertTrampoline(call_dest);
		RLBinUtils::RLBin_Debug("STATUS    :    DC51", __FILENAME__, __LINE__);			
	}
	else
	{
		// Check Call Dest Middle of function
		RLBinUtils::RLBin_Debug("STATUS    :    DC3", __FILENAME__, __LINE__);

		// Register function
		RLBinUtils::RLBin_Debug("STATUS    :    DC4", __FILENAME__, __LINE__);
	}
	return;
}

void CU::HandleNewNC(ADDRESS _address)
{
	// Check Next Inst Discovered
	RLBinUtils::RLBin_Debug("STATUS    :    NC1", __FILENAME__, __LINE__);

	Inst current;
	Disassembler::Get()->GetOneInst(_address, &current);
	ADDRESS next_inst = _address + current.size;
	if(DisTable::Get()->GetEntry(next_inst) == LOC_UNDISCOVERD)
	{
		// Check Next Inst Middle of function
		RLBinUtils::RLBin_Debug("STATUS    :    NC21", __FILENAME__, __LINE__);

		// Register function
		RLBinUtils::RLBin_Debug("STATUS    :    NC32", __FILENAME__, __LINE__);

		// Put trap to be discovered
		TMU::Get()->InsertTrampoline(next_inst);
		RLBinUtils::RLBin_Debug("STATUS    :    NC41", __FILENAME__, __LINE__);			
	}
	else
	{
	}
	return;
}

void CU::HandleNewDJ(ADDRESS _address)
{
	// Target of conditional or unconditional jump
	ADDRESS jump_target;

	if(Disassembler::Get()->IsInstConditionalJump(_address))
	{
		Inst current;
		Disassembler::Get()->GetOneInst(_address, &current);
		ADDRESS next_inst = _address + current.size;

		ADDRESS targets[2];
		Disassembler::Get()->GetConditionalCTIDest(_address, targets);
		jump_target = targets[0];

		// Check Next Inst Discovered
		RLBinUtils::RLBin_Debug("STATUS    :    DJ1_F", __FILENAME__, __LINE__);
		if(DisTable::Get()->GetEntry(next_inst) == LOC_UNDISCOVERD)
		{
			// Check Next Inst Within Current Function
			RLBinUtils::RLBin_Debug("STATUS    :    DJ22_F", __FILENAME__, __LINE__);

			// Add to pre type 1
			RLBinUtils::RLBin_Debug("STATUS    :    DJ33_F", __FILENAME__, __LINE__);

			// Put trap to be discovered
			TMU::Get()->InsertTrampoline(next_inst);
			RLBinUtils::RLBin_Debug("STATUS    :    DJ43_F", __FILENAME__, __LINE__);			
		}
		else
		{
		}		
	}
	else
	{
		Disassembler::Get()->GetDirectCTIDest(_address, &jump_target);
	}

	RLBinUtils::RLBin_Debug("jump target is " + RLBinUtils::ConvertHexToString(jump_target), __FILENAME__, __LINE__);

	// Now we handle the target
	// Check Next Inst Discovered
	RLBinUtils::RLBin_Debug("STATUS    :    DJ1_T", __FILENAME__, __LINE__);
	if(DisTable::Get()->GetEntry(jump_target) == LOC_UNDISCOVERD)
	{
		// Check Next Inst Within Current Function
		RLBinUtils::RLBin_Debug("STATUS    :    DJ22_T", __FILENAME__, __LINE__);

		// Add to pre type 1
		RLBinUtils::RLBin_Debug("STATUS    :    DJ33_T", __FILENAME__, __LINE__);

		// Put trap to be discovered
		TMU::Get()->InsertTrampoline(jump_target);
		RLBinUtils::RLBin_Debug("STATUS    :    DJ43_T", __FILENAME__, __LINE__);			
	}
	else
	{
	}		
	return;
}

void CU::HandleNewR(ADDRESS _address, ADDRESS _return_address)
{
	// Check against type 2 and pre type 2
	RLBinUtils::RLBin_Debug("STATUS    :    R1", __FILENAME__, __LINE__);

	// Analyze safety and modify disassembly table
	RLBinUtils::RLBin_Debug("STATUS    :    R2", __FILENAME__, __LINE__);

	// Check External Dest
	RLBinUtils::RLBin_Debug("STATUS    :    R3", __FILENAME__, __LINE__);
	if(!Modules::Get()->IsInsideMainCode(_return_address))
	{
		// Create instrumentation and check external
		RLBinUtils::RLBin_Debug("STATUS    :    R63", __FILENAME__, __LINE__);

		// Insert Trampoline to instrumentation			
		RLBinUtils::RLBin_Debug("STATUS    :    R71", __FILENAME__, __LINE__);			
	}
	else
	{
		// Check return address discovered
		RLBinUtils::RLBin_Debug("STATUS    :    R4", __FILENAME__, __LINE__);
		if(DisTable::Get()->GetEntry(_return_address) == LOC_UNDISCOVERD)
		{
			// Put trap to be discovered
			TMU::Get()->InsertTrampoline(_return_address);
			RLBinUtils::RLBin_Debug("STATUS    :    R5", __FILENAME__, __LINE__);

			// Create Instrumentation to checkDest against type 1			
			RLBinUtils::RLBin_Debug("STATUS    :    R62", __FILENAME__, __LINE__);

			// Insert Trampoline and Bypass			
			RLBinUtils::RLBin_Debug("STATUS    :    R72", __FILENAME__, __LINE__);			
		}
		else
		{
			// Create Instrumentation to checkDest against type 2			
			RLBinUtils::RLBin_Debug("STATUS    :    R61", __FILENAME__, __LINE__);			

			// Insert Trampoline to instrumentation			
			RLBinUtils::RLBin_Debug("STATUS    :    R71", __FILENAME__, __LINE__);			
		}

	}

	return;
}

void CU::HandleNewICJ(ADDRESS _address, ADDRESS _cj_address, ADDRESS _next_inst)
{	
	// Check External Dest
	RLBinUtils::RLBin_Debug("STATUS    :    ICJ2", __FILENAME__, __LINE__);
	if(!Modules::Get()->IsInsideMainCode(_cj_address))
	{
		// Check Call Back
		RLBinUtils::RLBin_Debug("STATUS    :    ICJ32", __FILENAME__, __LINE__);

		// Check next inst discovered?
		RLBinUtils::RLBin_Debug("STATUS    :    ICJ53", __FILENAME__, __LINE__);		
		if(DisTable::Get()->GetEntry(_next_inst) == LOC_UNDISCOVERD)
		{			
			// Put trap to be discovered
			RLBinUtils::RLBin_Debug("STATUS    :    ICJ82", __FILENAME__, __LINE__);		

			// Create instrumentation to check for external dest
			RLBinUtils::RLBin_Debug("STATUS    :    ICJ93", __FILENAME__, __LINE__);		

			// Insert trampoline and bypass (trap to be discovered)
			TMU::Get()->InsertTrampoline(_next_inst);
			RLBinUtils::RLBin_Debug("STATUS    :    ICJA3", __FILENAME__, __LINE__);		
		}
	}
	else
	{
		// Check target discovered?
		RLBinUtils::RLBin_Debug("STATUS    :    ICJ31", __FILENAME__, __LINE__);		
		if(DisTable::Get()->GetEntry(_cj_address) == LOC_UNDISCOVERD)
		{			
			// Create instrumentation to check against type 1
			RLBinUtils::RLBin_Debug("STATUS    :    ICJ91", __FILENAME__, __LINE__);		

			// Insert trampoline and bypass (trap to be discovered)
			TMU::Get()->InsertTrampoline(_cj_address);
			RLBinUtils::RLBin_Debug("STATUS    :    ICJA1", __FILENAME__, __LINE__);		
		}		
	}
}