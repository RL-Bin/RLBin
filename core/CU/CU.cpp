/**
 * @file CU.cpp
 * @brief Defines the body of functions in CU class.
 */

#include "..\include\CU\CU.h"


#include "..\include\TMU\TMU.h"
#include "..\include\IMU\IMU.h"

#include "..\include\SubUnits\Modules\Modules.h"
#include "..\include\SubUnits\Disassembler\Disassembler.h"
#include "..\include\DataStructs\DisTable\DisTable.h"

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

	DisTable::Create();
	DisTable::Get()->Initialize(Modules::Get()->GetMainModule()->module_size);

	TMU::Create();
	TMU::Get()->Initialize();
}
