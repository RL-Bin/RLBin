/**
 * @file InstRoutines.cpp
 * @brief Defines the functions that create instrumentation for different types of indirect CTIs.
 */

#include "..\include\IMU\IMU.h"
#include "..\include\FAU\FAU.h"
#include "..\include\SubUnits\Modules\Modules.h"
#include "..\include\DataStructs\DisTable\DisTable.h"

/** This function will be called so that exception handler gets updated */
extern void InitGlobals();


void CopyAddedRoutine(BYTE *_added_routine, int _size, ADDRESS _dest_address)
{
	for(int i=0; i<_size; i++)
	{
		*(BYTE *)(_dest_address + i) = _added_routine[i];
	}
}

ADDRESS IMU::CreateInstRoutine_0xC3()
{
	// 0:  50                      push   eax
	// 1:  9c                      pushf
	// 2:  8b 44 24 08             mov    eax,DWORD PTR [esp+0x8]
	// 6:  3d 78 56 34 12          cmp    eax,0x12345678
	// b:  7c 13                   jl     20 <end>
	// d:  3d 98 ba dc fe          cmp    eax,0xfedcba98
	// 12: 7f 0c                   jg     20 <end>
	// 14: 05 44 33 22 11          add    eax,0x11223344
	// 19: 8b 00                   mov    eax,DWORD PTR [eax]
	// 1b: 83 f8 00                cmp    eax,0x0
	// 1e: 74 03                   je     23 <check>
	// 00000020 <end>:
	// 20: 9d                      popf
	// 21: 58                      pop    eax
	// 22: c3                      ret
	// 00000023 <check>:
	// 23: 9d                      popf
	// 24: 8b 44 24 08             mov    eax,DWORD PTR [esp+0x4]
	// 28: cc                      int3
	// 29: 58					   pop eax
	// 2A: c3                      ret
	BYTE routine[] = { 0x50, 0x9C, 0x8B, 0x44, 0x24, 0x08, 0x3D, 0x78, 0x56, 0x34, 0x12, 0x7C, 
					   0x13, 0x3D, 0x98, 0xBA, 0xDC, 0xFE, 0x7F, 0x0C, 0x05, 0x44, 0x33, 0x22, 
					   0x11, 0x8B, 0x00, 0x83, 0xF8, 0x00, 0x74, 0x03, 0x9D, 0x58, 0xC3, 0x9D, 
					   0x8B, 0x44, 0x24, 0x04, 0xCC, 0x58, 0xC3};
	
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

	head = head + added_routine_size;

	return RetRoutine;
}

ADDRESS IMU::CreateInstRoutine_0xC2(ADDRESS _address)
{
	// 0:  50                      push   eax
	// 1:  9c                      pushf
	// 2:  8b 44 24 08             mov    eax,DWORD PTR [esp+0x8]
	// 6:  3d 78 56 34 12          cmp    eax,0x12345678
	// b:  7c 13                   jl     20 <end>
	// d:  3d 98 ba dc fe          cmp    eax,0xfedcba98
	// 12: 7f 0c                   jg     20 <end>
	// 14: 05 44 33 22 11          add    eax,0x11223344
	// 19: 8b 00                   mov    eax,DWORD PTR [eax]
	// 1b: 83 f8 00                cmp    eax,0x0
	// 1e: 74 05                   je     25 <check>
	// 00000020 <end>:
	// 20: 9d                      popf
	// 21: 58                      pop    eax
	// 22: c2 04 00                ret 0x4
	// 00000025 <check>:
	// 25: 9d                      popf
	// 26: 8b 44 24 08             mov    eax,DWORD PTR [esp+0x4]
	// 2A: cc                      int3
	// 2B: 58					   pop eax
	// 2C: c2 04 00                ret 0x4
	BYTE routine[] = { 0x50, 0x9C, 0x8B, 0x44, 0x24, 0x08, 0x3D, 0x78, 0x56, 0x34, 0x12, 0x7C, 
					   0x13, 0x3D, 0x98, 0xBA, 0xDC, 0xFE, 0x7F, 0x0C, 0x05, 0x44, 0x33, 0x22, 
					   0x11, 0x8B, 0x00, 0x83, 0xF8, 0x00, 0x74, 0x05, 0x9D, 0x58, 0xC2, 0x04,
					   0x00, 0x9D, 0x8B, 0x44, 0x24, 0x04, 0xCC, 0x58, 0xC2, 0x04, 0x00};
	
	int added_routine_size = (sizeof(routine)/sizeof((routine)[0]));

	ADDRESS base = Modules::Get()->GetMainModule()->base_address;
	ADDRESS end = base + Modules::Get()->GetMainModule()->module_size;
	ADDRESS offset = DisTable::Get()->GetOffset();

	*(ADDRESS *) (routine+7) = base;
	*(ADDRESS *) (routine+14) = end;
	*(ADDRESS *) (routine+21) = offset;

	*(byte *) (routine+35) = *((byte *) (_address)+1);
	*(byte *) (routine+36) = *((byte *) (_address)+2);

	*(byte *) (routine+45) = *((byte *) (_address)+1);
	*(byte *) (routine+46) = *((byte *) (_address)+2);

	// writing routine
	CopyAddedRoutine(routine, added_routine_size, head);

	ADDRESS C2Routine = head;

	head = head + added_routine_size;

	return C2Routine;
}

ADDRESS IMU::CreateInstRoutine_0xFF15(ADDRESS _address)
{
	// 0:  50                      push   eax
	// 1:  9c                      pushf
	// 2:  ff 05 aa aa aa aa       inc    DWORD PTR ds:0xaaaaaaaa
	// 8:  a1 bb bb bb bb          mov    eax,ds:0xbbbbbbbb
	// d:  3d cc cc cc cc          cmp    eax,0xcccccccc
	// 12: 75 07                   jne    1b <end>
	// 14: 9d                      popf
	// 15: 58                      pop    eax
	// 16: e9 c8 cc cc cc          jmp   cccccce3 <end+0xccccccc8>
	// 0000001b <end>:
	// 1b: 9d                      popf
	// 1c: 58                      pop    eax
	// 1d: cc                      int3

	BYTE routine[] = { 0x50, 0x9C, 0xFF, 0x05, 0xAA, 0xAA, 0xAA, 0xAA, 0xA1, 0xBB, 0xBB, 0xBB, 0xBB,
	 				   0x3D, 0xCC, 0xCC, 0xCC, 0xCC, 0x75, 0x07, 0x9D, 0x58, 0xE9, 0xC8, 0xCC, 0xCC, 
	 				   0xCC, 0x9D, 0x58, 0xCC };
	
	int added_routine_size = (sizeof(routine)/sizeof((routine)[0]));

	*(ADDRESS *) (routine+4) = (ADDRESS)(&(FAU::Get()->count__check_0xFF15));

	*(ADDRESS *) (routine+9) = *(ADDRESS *)((byte *)_address+2);

	*(ADDRESS *) (routine+14) = *(ADDRESS *)(*(ADDRESS *)((byte *)_address+2));
	
	*(ADDRESS *) (routine+23) = (*(ADDRESS *)(*(ADDRESS *)((byte *)_address+2))) - ((ADDRESS)(head+27));

	// writing routine
	CopyAddedRoutine(routine, added_routine_size, head);

	ADDRESS Routine_FF15 = head;

	head = head + added_routine_size;

	return Routine_FF15;
}

ADDRESS IMU::CreateInstRoutine_0xFFD(ADDRESS _address)
{
	// 0:  50                      push   eax
	// 1:  9c                      pushf
	// 2:  89 d8                   mov    eax,ebx
	// 4:  3d 78 56 34 12          cmp    eax,0x12345678
	// 9:  7c 13                   jl     1e <end>
	// b:  3d 98 ba dc fe          cmp    eax,0xfedcba98
	// 10: 7f 0c                   jg     1e <end>
	// 12: 05 44 33 22 11          add    eax,0x11223344
	// 17: 8b 00                   mov    eax,DWORD PTR [eax]
	// 19: 83 f8 00                cmp    eax,0x0
	// 1c: 74 09                   je     27 <check>
	// 0000001e <end>:
	// 1e: 9d                      popf
	// 1f: 58                      pop    eax
	// 20: 68 78 56 34 12          push   0x12345678
	// 25: ff e0                   jmp    eax
	// 00000027 <check>:
	// 27: 9d                      popf
	// 28: 89 d8                   mov eax,ebx
	// 2A: cc                      int3
	// 2B: 58                      pop    eax
	// 2C: 68 78 56 34 12          push   0x12345678
	// 31: ff e0                   jmp    eax

	BYTE routine[] = { 0x50, 0x9C, 0x89, 0xD8, 0x3D, 0x78, 0x56, 0x34, 0x12, 0x7C, 0x13, 0x3D, 0x98, 0xBA, 0xDC, 0xFE, 
		               0x7F, 0x0C, 0x05, 0x44, 0x33, 0x22, 0x11, 0x8B, 0x00, 0x83, 0xF8, 0x00, 0x74, 0x09, 0x9D, 0x58, 
		               0x68, 0x78, 0x56, 0x34, 0x12, 0xFF, 0xE0, 0x9D, 0x89, 0xD8, 0xCC, 0x58, 0x68, 0x78, 0x56, 0x34,
		               0x12, 0xFF, 0xE0 };
	
	int added_routine_size = (sizeof(routine)/sizeof((routine)[0]));

	ADDRESS base = Modules::Get()->GetMainModule()->base_address;
	ADDRESS end = base + Modules::Get()->GetMainModule()->module_size;
	ADDRESS offset = DisTable::Get()->GetOffset();

	*(byte *) (routine+3) = ((*(byte *) (routine+3)) & 0xC7) | (((*((byte *)_address + 1)) & 0x07) << 3);

	*(ADDRESS *) (routine+5) = base;
	*(ADDRESS *) (routine+12) = end;
	*(ADDRESS *) (routine+19) = offset;

	*(ADDRESS *) (routine+33) = (_address+2);

	*(byte *) (routine+38) = ((*(byte *) (routine+38)) & 0xF8) | (((*((byte *)_address + 1)) & 0x07));

	*(byte *) (routine+41) = ((*(byte *) (routine+41)) & 0xC7) | (((*((byte *)_address + 1)) & 0x07) << 3);

	*(ADDRESS *) (routine+45) = (_address+2);

	*(byte *) (routine+50) = ((*(byte *) (routine+50)) & 0xF8) | (((*((byte *)_address + 1)) & 0x07));

	// writing routine
	CopyAddedRoutine(routine, added_routine_size, head);

	ADDRESS Routine_FFD = head;

	head = head + added_routine_size;

	return Routine_FFD;
}
