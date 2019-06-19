/**
 * @file Inst.cpp
 * @brief Implements the main functions of the Inst class  
 */

#include "..\..\include\SubUnits\Disassembler\Inst.h"

void Inst::GetFromCapstone(int _id, ADDRESS _address, SIZE_TYPE _size, uint8_t *_bytes, char *_mnemonic, char *_op_str,
 						   uint8_t *_prefix, uint8_t *_opcode, uint8_t _addr_size, uint8_t _modrm, uint8_t _sib, 
 						   int32_t _disp, x86_reg _sib_index, int8_t _sib_scale, x86_reg _sib_base, uint8_t _op_count, 
 						   cs_x86_op *_operands)
{
	type = OTHER;
	id = _id;
	address = _address;
	size = _size;
	for(int i=0; i<16; i++)
	{
		bytes[i]= _bytes[i];
	}
	for(int i=0; i<32; i++)
	{
		mnemonic[i]= _mnemonic[i];
	}
	for(int i=0; i<160; i++)
	{
		op_str[i]= _op_str[i];
	}
	for(int i=0; i<4; i++)
	{
		prefix[i] = _prefix[i];
		opcode[i] = _opcode[i];
	}
	addr_size = _addr_size;
	modrm = _modrm;
	sib = _sib;
	disp = _disp;
	sib_index = _sib_index;
	sib_scale = _sib_scale;
	sib_base = _sib_base;
	op_count = _op_count;
	for(int i=0; i<8; i++)
	{
		operands[i]= _operands[i];
	}
}
