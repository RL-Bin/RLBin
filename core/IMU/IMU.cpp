/**
 * @file IMU.cpp
 * @brief Defines the body of functions in IMU class.
 */

#include "..\include\IMU\IMU.h"
#include "..\include\SubUnits\Modules\Modules.h"
#include "..\include\DataStructs\DisTable\DisTable.h"

// inititalizing the only instace of class 
IMU* IMU::s_instance = NULL;

void CopyAddedRoutine(BYTE *_added_routine, int _size, ADDRESS _dest_address)
{
	for(int i=0; i<_size; i++)
	{
		*(BYTE *)(_dest_address + i) = _added_routine[i];
	}
}


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


ADDRESS IMU::CreateInstRoutineRet()
{
	// 0:  50                      push   eax
	// 1:  9c                      pushf
	// 2:  8b 44 24 08             mov    eax,DWORD PTR [esp+0x8]
	// 6:  3d 78 56 34 12          cmp    eax,0x12345678
	// b:  7c 16                   jl     23 <end>
	// d:  3d 98 ba dc fe          cmp    eax,0xfedcba98
	// 12: 7f 0f                   jg     23 <end>
	// 14: 05 44 33 22 11          add    eax,0x11223344
	// 19: 8b 00                   mov    eax,DWORD PTR [eax]
	// 1b: 83 f8 00                cmp    eax,0x0
	// 1e: 74 03                   je     23 <end>
	// 20: 9d                      popf
	// 21: 58                      pop    eax
	// 22: c3                      ret
	// 00000023 <end>:
	// 23: 9d                      popf
	// 24: 58                      pop    eax
	// 25: cc                      int3
	BYTE routine[] = { 0x50, 0x9C, 0x8B, 0x44, 0x24, 0x08, 0x3D, 0x78, 0x56, 0x34, 0x12, 0x7C, 0x16, 
					   0x3D, 0x98, 0xBA, 0xDC, 0xFE, 0x7F, 0x0F, 0x05, 0x44, 0x33, 0x22, 0x11, 0x8B, 
					   0x00, 0x83, 0xF8, 0x00, 0x74, 0x03, 0x9D, 0x58, 0xC3, 0x9D, 0x58, 0xCC };
	
	int added_routine_size = (sizeof(routine)/sizeof((routine)[0]));

	ADDRESS base = Modules::Get()->GetMainModule()->base_address;
	ADDRESS end = base + Modules::Get()->GetMainModule()->module_size;
	ADDRESS offset = DisTable::Get()->GetOffset();

	*(ADDRESS *) (routine+7) = base;
	*(ADDRESS *) (routine+14) = end;
	*(ADDRESS *) (routine+21) = offset;

	// writing routine
	CopyAddedRoutine(routine, added_routine_size, head);

	RetRoutine = head;

	head = head + DEFAULT_ROUTINE_SIZE;

	return RetRoutine;
}
