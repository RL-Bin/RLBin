/**
 * @file IMU.cpp
 * @brief Defines the body of functions in IMU class.
 */

#include "..\include\IMU\IMU.h"
#include "..\include\SubUnits\Modules\Modules.h"
#include "..\include\SubUnits\Disassembler\Disassembler.h"

// inititalizing the only instace of class 
IMU* IMU::s_instance = NULL;

IMU* IMU::Create(void) 
{
	if (s_instance != NULL)
	{
		RLBinUtils::RLBin_Error("An instance of IMU exists", __FILENAME__, __LINE__);
		return NULL;
	}
	s_instance = new IMU();
	return s_instance;
}

IMU* IMU::Get(void) 
{
	if (s_instance == NULL)
	{
		RLBinUtils::RLBin_Error("IMU is not initialized yet!", __FILENAME__, __LINE__);
		return NULL;
	}
	return s_instance;
}

void IMU::Initialize(void) 
{
	instrumentations = new byte[SIZE_INSTRUMENATION];

	head = (ADDRESS) instrumentations;

	RLBinUtils::SetExecutePermission((ADDRESS)instrumentations, SIZE_INSTRUMENATION);

	return;
}

ADDRESS IMU::CreateInstRoutine(ADDRESS _address)
{
	// First, create a key based on the first 8 byte of Ind CTI
	DWORD64 key = CreateKey(_address);
	//printf("%08x %08x\n", *((ADDRESS *)(&key)+1), *(ADDRESS *)(&key));

	if(inst_map.find(key) == inst_map.end())
	{
		if((key & 0x000000FF) == 0x000000C3)
		{
			inst_map [key] = CreateInstRoutine_0xC3();
			PrintRoutine(_address, inst_map[key], 19);
		}
		if((key & 0x000000FF) == 0x000000C2)
		{
			inst_map [key] = CreateInstRoutine_0xC2(_address);
			PrintRoutine(_address, inst_map[key], 19);
		}
		else if((key & 0x0000FFFF) == 0x000015FF)
		{
			inst_map [key] = CreateInstRoutine_0xFF15(_address);
			PrintRoutine(_address, inst_map[key], 12);
		}		
		else if((key & 0x0000F0FF) == 0x0000D0FF)
		{
			inst_map [key] = CreateInstRoutine_0xFFD(_address);
			PrintRoutine(_address, inst_map[key], 21);
		}
		else
		{
			return 0;
		}
	}
	return inst_map [key];
}

void IMU::PrintRoutine(ADDRESS _inst, ADDRESS _routine, int size)
{
	RLBinUtils::RLBin_Inst("__________________________________________________________");
	Disassembler::Get()->PrintInst(_inst, T_INST);
	RLBinUtils::RLBin_Inst("_________________________");
	Disassembler::Get()->PrintNInsts(_routine, T_INST, size);
	return;
}

void IMU::PrintRoutinesSize()
{
	RLBinUtils::RLBin_Inst("__________________________________________________________");
	RLBinUtils::RLBin_Inst("__________________________________________________________");
	RLBinUtils::RLBin_Inst("Total Size of instrumentation : " + RLBinUtils::ConvertHexToString(head - (ADDRESS)instrumentations));
	RLBinUtils::RLBin_Inst("__________________________________________________________");
	RLBinUtils::RLBin_Inst("__________________________________________________________");
	return;
}

DWORD64 IMU::CreateKey(ADDRESS _address)
{
	int size = Disassembler::Get()->GetInstSize(_address);
	DWORD64 key = *(DWORD64 *) _address;
	for(int i=size; i<8; i++)
	{
		*((byte *)(&key) + i) = 0;
	}

	if((key & 0x0000F0FF) == 0x0000D0FF)
	{
		*((ADDRESS *)(&key)+1) = _address;
	}

	return key;
}
