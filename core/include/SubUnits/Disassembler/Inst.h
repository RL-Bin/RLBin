#ifndef _INST_H
#define _INST_H

/**
 * @file Inst.h 
 * @brief This file contains Inst class for keeping information of a single instruction 
 */

#include "..\..\SubUnits\Utils\defs.h"
#include "..\..\SubUnits\Utils\RLBinUtils.h"

#include "..\..\Capstone\capstone.h"
#include "..\..\Capstone\platform.h"

/**
 * @class Inst
 * @brief This class will hold single instructions which will be used in our instrumentation routine or trap
 */
class Inst
{
public:
	/** Default constuctor of Inst class */
	Inst(){}

	/** Default destuctor of Inst class */
	~Inst(){}

	/** 
	 * @brief Reads the instruction information from capstone library 
	 *
	 * @param [in] _id Unique ID of each instruction
	 * @param [in] _address The address of the instruction
	 * @param [in] _size The number of bytes in instruction
	 * @param [in] _bytes The bytes that create an instruction
	 * @param [in] _mnemonic The mnemonic of the instruction
	 * @param [in] _op_str The instruction in string form
	 * @param [in] _prefix The prefix of the instruction
	 * @param [in] _opcode The opcode of the instruction
	 * @param [in] _addr_size The addressing mode of the instruction
	 * @param [in] _modrm The three MODRM bits of the instruction
	 * @param [in] _sib The three SIB bits of the instruction
	 * @param [in] _disp The displacement the instruction
	 * @param [in] _sib_index The SIB index of the instruction 
	 * @param [in] _sib_scale The SIB scale value of the instruction
	 * @param [in] _sib_base The SIB base value of the instruction 
	 * @param [in] _op_count The number of operands in the instruction
	 * @param [in] _operands The operands of the instruction
	 */
	void GetFromCapstone(int _id, ADDRESS _address, SIZE_TYPE _size, uint8_t *_bytes, char *_mnemonic, char *_op_str,
 						 uint8_t *_prefix, uint8_t *_opcode, uint8_t _addr_size, uint8_t _modrm, uint8_t _sib, 
 						 int32_t _disp, x86_reg _sib_index, int8_t _sib_scale, x86_reg _sib_base, uint8_t _op_count, cs_x86_op *_operands);

	/** Type of instruction */
	InstType type;

	/** Unique ID of each instruction */
	unsigned int id;

	/** The address of the instruction */
	ADDRESS address;

	/** The number of bytes in instruction */
	SIZE_TYPE size;

	/** The bytes that create an instruction */
	uint8_t bytes[16];

	/** The mnemonic of the instruction */
	char mnemonic[32];

	/** The instruction in string form*/
	char op_str[160];

	/** The prefix of the instruction */
	uint8_t prefix[4];

	/** The opcode of the instruction */
	uint8_t opcode[4];

	/** The addressing mode of the instruction */
	uint8_t addr_size;

	/** The three MODRM bits of the instruction */
	uint8_t modrm;
	
	/** The three SIB bits of the instruction */
	uint8_t sib;
	
	/** The displacement the instruction */
	int32_t disp;
	
	/** The SIB index of the instruction */
	x86_reg sib_index;

	/** The SIB scale value of the instruction */
	int8_t sib_scale;

	/** The SIB base value of the instruction */
	x86_reg sib_base;

	/** The number of operands in the instruction */
	uint8_t op_count;

	/** The operands of the instruction */
	cs_x86_op operands[8];	
};	

#endif