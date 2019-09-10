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

ADDRESS IMU::CreateInstRoutine_0xF2C3()
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
	// 1e: 74 04                   je     24 <check>
	// 00000020 <end>:
	// 20: 9d                      popf
	// 21: 58                      pop    eax
	// 22: f2 c3                   bnd ret
	// 00000024 <check>:
	// 24: 9d                      popf
	// 25: 8b 44 24 08             mov    eax,DWORD PTR [esp+0x4]
	// 29: cc                      int3
	// 2A: 58					   pop eax
	// 2B: f2 c3                   bnd ret
	BYTE routine[] = { 0x50, 0x9C, 0x8B, 0x44, 0x24, 0x08, 0x3D, 0x78, 0x56, 0x34, 0x12, 0x7C, 
					   0x13, 0x3D, 0x98, 0xBA, 0xDC, 0xFE, 0x7F, 0x0C, 0x05, 0x44, 0x33, 0x22, 
					   0x11, 0x8B, 0x00, 0x83, 0xF8, 0x00, 0x74, 0x04, 0x9D, 0x58, 0xF2, 0xC3, 
					   0x9D, 0x8B, 0x44, 0x24, 0x04, 0xCC, 0x58, 0xF2, 0xC3};
	
	int added_routine_size = (sizeof(routine)/sizeof((routine)[0]));

	ADDRESS base = Modules::Get()->GetMainModule()->base_address;
	ADDRESS end = base + Modules::Get()->GetMainModule()->module_size;
	ADDRESS offset = DisTable::Get()->GetOffset();

	*(ADDRESS *) (routine+7) = base;
	*(ADDRESS *) (routine+14) = end;
	*(ADDRESS *) (routine+21) = offset;

	// writing routine
	CopyAddedRoutine(routine, added_routine_size, head);

	ADDRESS F2C3Routine = head;

	head = head + added_routine_size;

	return F2C3Routine;
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

ADDRESS IMU::CreateInstRoutine_0xFF25(ADDRESS _address)
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

	*(ADDRESS *) (routine+4) = (ADDRESS)(&(FAU::Get()->count__check_0xFF25));

	*(ADDRESS *) (routine+9) = *(ADDRESS *)((byte *)_address+2);

	*(ADDRESS *) (routine+14) = *(ADDRESS *)(*(ADDRESS *)((byte *)_address+2));
	
	*(ADDRESS *) (routine+23) = (*(ADDRESS *)(*(ADDRESS *)((byte *)_address+2))) - ((ADDRESS)(head+27));

	// writing routine
	CopyAddedRoutine(routine, added_routine_size, head);

	ADDRESS Routine_FF25 = head;

	head = head + added_routine_size;

	return Routine_FF25;
}

ADDRESS IMU::CreateInstRoutine_0x3EFFE(ADDRESS _address)
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
	// 1c: 74 05                   je     23 <check>
	// 0000001e <end>:
	// 1e: 9d                      popf
	// 1f: 58                      pop    eax
	// 20: 3e ff e0                jmp    eax
	// 00000023 <check>:
	// 23: 9d                      popf
	// 24: 89 d8                   mov eax,ebx
	// 26: cc                      int3
	// 27: 58                      pop    eax
	// 28: 3e ff e0                jmp    eax

	BYTE routine[] = { 0x50, 0x9C, 0x89, 0xD8, 0x3D, 0x78, 0x56, 0x34, 0x12, 0x7C, 0x13, 0x3D, 0x98, 0xBA, 0xDC, 0xFE, 
		               0x7F, 0x0C, 0x05, 0x44, 0x33, 0x22, 0x11, 0x8B, 0x00, 0x83, 0xF8, 0x00, 0x74, 0x05, 0x9D, 0x58, 
		               0x3E, 0xFF, 0xE0, 0x9D, 0x89, 0xD8, 0xCC, 0x58, 0x3E, 0xFF, 0xE0 };
	
	int added_routine_size = (sizeof(routine)/sizeof((routine)[0]));

	ADDRESS base = Modules::Get()->GetMainModule()->base_address;
	ADDRESS end = base + Modules::Get()->GetMainModule()->module_size;
	ADDRESS offset = DisTable::Get()->GetOffset();

	*(byte *) (routine+3) = ((*(byte *) (routine+3)) & 0xC7) | (((*((byte *)_address + 2)) & 0x07) << 3);

	*(ADDRESS *) (routine+5) = base;
	*(ADDRESS *) (routine+12) = end;
	*(ADDRESS *) (routine+19) = offset;

	*(byte *) (routine+34) = ((*(byte *) (routine+34)) & 0xF8) | (((*((byte *)_address + 2)) & 0x07));

	*(byte *) (routine+37) = ((*(byte *) (routine+37)) & 0xC7) | (((*((byte *)_address + 2)) & 0x07) << 3);

	*(byte *) (routine+42) = ((*(byte *) (routine+42)) & 0xF8) | (((*((byte *)_address + 2)) & 0x07));

	// writing routine
	CopyAddedRoutine(routine, added_routine_size, head);

	ADDRESS Routine_3EFFE = head;

	head = head + added_routine_size;

	return Routine_3EFFE;
}

ADDRESS IMU::CreateInstRoutine_0xFF2485(ADDRESS _address)
{
	// 0:  50                      push   eax
	// 1:  9c                      pushf
	// 2:  ff 05 aa aa aa aa       inc    DWORD PTR ds:0xaaaaaaaa
	// 8:  8b 04 85 44 33 22 11    mov    eax,DWORD PTR [eax*4+0x11223344]
	// f:  3d 78 56 34 12          cmp    eax,0x12345678
	// 14: 7c 13                   jl     29 <end>
	// 16: 3d 98 ba dc fe          cmp    eax,0xfedcba98
	// 1b: 7f 0c                   jg     29 <end>
	// 1d: 05 44 33 22 11          add    eax,0x11223344
	// 22: 8b 00                   mov    eax,DWORD PTR [eax]
	// 24: 83 f8 00                cmp    eax,0x0
	// 27: 74 09                   je     32 <check>
	// 00000029 <end>:
	// 29: 9d                      popf
	// 2a: 58                      pop    eax
	// 2b: ff 24 85 44 33 22 11    jmp    DWORD PTR [eax*4+0x11223344]
	// 00000032 <check>:
	// 32: 9d                      popf
	// 33: 8b 04 85 44 33 22 11    mov    eax,DWORD PTR [eax*4+0x11223344]
	// 3a: cc                      int3
	// 3b: 58                      pop    eax
	// 3c: ff 24 85 44 33 22 11    jmp    DWORD PTR [eax*4+0x11223344]

	BYTE routine[] = { 0x50, 0x9C, 0xFF, 0x05, 0xAA, 0xAA, 0xAA, 0xAA, 0x8B, 0x04, 0x85, 0x44, 0x33, 0x22, 0x11, 
		               0x3D, 0x78, 0x56, 0x34, 0x12, 0x7C, 0x13, 0x3D, 0x98, 0xBA, 0xDC, 0xFE, 0x7F, 0x0C, 0x05, 
		               0x44, 0x33, 0x22, 0x11, 0x8B, 0x00, 0x83, 0xF8, 0x00, 0x74, 0x09, 0x9D, 0x58, 0xFF, 0x24, 
		               0x85, 0x44, 0x33, 0x22, 0x11, 0x9D, 0x8B, 0x04, 0x85, 0x44, 0x33, 0x22, 0x11, 0xCC, 0x58, 
		               0xFF, 0x24, 0x85, 0x44, 0x33, 0x22, 0x11 };
	
	int added_routine_size = (sizeof(routine)/sizeof((routine)[0]));

	ADDRESS base = Modules::Get()->GetMainModule()->base_address;
	ADDRESS end = base + Modules::Get()->GetMainModule()->module_size;
	ADDRESS offset = DisTable::Get()->GetOffset();

	*(ADDRESS *) (routine+4) = (ADDRESS)(&(FAU::Get()->count__check_0xFF2485));

	*(byte *) (routine+10) = *((byte *)_address + 2);
	*(ADDRESS *) (routine+11) = *((ADDRESS *)(_address + 3));	

	*(ADDRESS *) (routine+16) = base;
	*(ADDRESS *) (routine+23) = end;
	*(ADDRESS *) (routine+30) = offset;

	*(byte *) (routine+0x2D) = *((ADDRESS *)(_address + 2));
	*(ADDRESS *) (routine+0x2E) = *((ADDRESS *)(_address + 3));	

	*(byte *) (routine+0x35) = *((byte *)_address + 2);
	*(ADDRESS *) (routine+0x36) = *((ADDRESS *)(_address + 3));	

	*(byte *) (routine+0x3E) = *((ADDRESS *)(_address + 2));
	*(ADDRESS *) (routine+0x3F) = *((ADDRESS *)(_address + 3));	


	// writing routine
	CopyAddedRoutine(routine, added_routine_size, head);

	ADDRESS Routine_FF2485 = head;

	head = head + added_routine_size;

	return Routine_FF2485;
}

ADDRESS IMU::CreateInstRoutine_0xFF5(ADDRESS _address)
{
	// 0:  50                      push   eax
	// 1:  9c                      pushf
	// 2:  8b 40 01                mov    eax,DWORD PTR [eax+0x1]
	// 5:  3d 78 56 34 12          cmp    eax,0x12345678
	// a:  7c 13                   jl     1f <end>
	// c:  3d 98 ba dc fe          cmp    eax,0xfedcba98
	// 11: 7f 0c                   jg     1f <end>
	// 13: 05 44 33 22 11          add    eax,0x11223344
	// 18: 8b 00                   mov    eax,DWORD PTR [eax]
	// 1a: 83 f8 00                cmp    eax,0x0
	// 1d: 74 0a                   je     29 <check>
	// 0000001f <end>:
	// 1f: 9d                      popf
	// 20: 58                      pop    eax
	// 21: 68 78 56 34 12          push   0x12345678
	// 26: ff 60 01                jmp    DWORD PTR [eax+0x1]
	// 00000029 <check>:
	// 29: 9d                      popf
	// 2a: 8b 40 01                mov    eax,DWORD PTR [eax+0x1]
	// 2d: cc                      int3
	// 2e: 58                      pop    eax
	// 2f: 68 78 56 34 12          push   0x12345678
	// 34: ff 60 01                jmp    DWORD PTR [eax+0x1]

	BYTE routine[] = { 0x50, 0x9C, 0x8B, 0x40, 0x01, 0x3D, 0x78, 0x56, 0x34, 0x12, 0x7C, 0x13, 0x3D, 
		               0x98, 0xBA, 0xDC, 0xFE, 0x7F, 0x0C, 0x05, 0x44, 0x33, 0x22, 0x11, 0x8B, 0x00, 
		               0x83, 0xF8, 0x00, 0x74, 0x0A, 0x9D, 0x58, 0x68, 0x78, 0x56, 0x34, 0x12, 0xFF, 
		               0x60, 0x01, 0x9D, 0x8B, 0x40, 0x01, 0xCC, 0x58, 0x68, 0x78, 0x56, 0x34, 0x12, 
		               0xFF, 0x60, 0x01 };
	
	int added_routine_size = (sizeof(routine)/sizeof((routine)[0]));

	ADDRESS base = Modules::Get()->GetMainModule()->base_address;
	ADDRESS end = base + Modules::Get()->GetMainModule()->module_size;
	ADDRESS offset = DisTable::Get()->GetOffset();

	*(byte *) (routine+3) = ((*(byte *) (routine+3)) & 0xF8) | ((*((byte *)_address + 1)) & 0x07);
	*(byte *) (routine+4) = *((byte *)_address + 2);

	*(ADDRESS *) (routine+6) = base;
	*(ADDRESS *) (routine+13) = end;
	*(ADDRESS *) (routine+20) = offset;

	*(ADDRESS *) (routine+0x22) = (_address+3);

	*(byte *) (routine+0x27) = ((*(byte *) (routine+0x27)) & 0xF8) | ((*((byte *)_address + 1)) & 0x07);
	*(byte *) (routine+0x28) = *((byte *)_address + 2);

	*(byte *) (routine+0x2b) = ((*(byte *) (routine+0x2b)) & 0xF8) | ((*((byte *)_address + 1)) & 0x07);
	*(byte *) (routine+0x2c) = *((byte *)_address + 2);

	*(ADDRESS *) (routine+0x30) = (_address+3);

	*(byte *) (routine+0x35) = ((*(byte *) (routine+0x35)) & 0xF8) | ((*((byte *)_address + 1)) & 0x07);
	*(byte *) (routine+0x36) = *((byte *)_address + 2);

	// writing routine
	CopyAddedRoutine(routine, added_routine_size, head);

	ADDRESS Routine_FF5 = head;

	head = head + added_routine_size;

	return Routine_FF5;
}