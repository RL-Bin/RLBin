#ifndef _DISASSEMBLER_H
#define _DISASSEMBLER_H

/**
 * @file Disassembler.h
 * @brief This file contains Disassembler class and functions which are responsible for disassembling the code
 */
#include <unordered_map>

#include "..\..\SubUnits\Utils\defs.h"
#include "..\..\SubUnits\Utils\RLBinUtils.h"

#include "..\..\Capstone\capstone.h"
#include "..\..\Capstone\platform.h"

#include "Inst.h"
#include "..\..\SubUnits\Modules\Modules.h"
#include "..\..\DataStructs\DisTable\DisTable.h"

/**
 * @class Disassembler
 * @brief Disassembler class contains disassmebly functions
 */
class Disassembler
{
public:

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////							Implemented in Disassembler.cpp						////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/** @brief Creates the single instance of the Disassembler class */
	static Disassembler* Create(void);

	/** @brief gets the single instance of the Disassembler class */
	static Disassembler* Get(void);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////													Implemented in Opcode.cpp									   /////////
	/////////			Series of helper functions which take care of disassembly and opcode of instruction 				   /////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/**
	 * @brief Checks if the instruction is return instruction
	 *
	 * @return true if the instruction is return 
	 */	
	bool IsInstRet(ADDRESS _address);

	/**
	 * @brief Checks if the instruction is direct jump
	 *
	 * @return true if the instruction is direct jump
	 */	
	bool IsInstDirectJump(ADDRESS _address);

	/**
	 * @brief Checks if the instruction is direct call
	 *
	 * @return true if the instruction is direct call
	 */	
	bool IsInstDirectCall(ADDRESS _address);

	/**
	 * @brief Checks if the instruction is conditional jump
	 *
	 * @return true if the instruction is conditional jump
	 */	
	bool IsInstConditionalJump(ADDRESS _address);

	/**
	 * @brief Checks if the instruction is an unconditional jump
	 *
	 * @return true if the instruction is unconditional jump
	 */	
	bool IsInstUnconditionalJump(ADDRESS _address);

	/**
	 * @brief Checks if the instruction is indirect jump
	 *
	 * @return true if the instruction is indirect jump
	 */	
	bool IsInstIndirectJump(ADDRESS _address);

	/**
	 * @brief Checks if the instruction is indirect call
	 *
	 * @return true if the instruction is indirect call
	 */
	bool IsInstIndirectCall(ADDRESS _address);


	/**
	 * @brief Checks if the instruction is direct CTI
	 *
	 * @return true if the instruction is direct CTI
	 */
	bool IsInstDirectCTI(ADDRESS _address);

	/**
	 * @brief Checks if the instruction is indirect CTI
	 *
	 * @return true if the instruction is indirect CTI
	 */
	bool IsInstIndirectCTI(ADDRESS _address);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////										Implemented in AddressTranslator.cpp									   /////////
	/////////			(1)	Series of helper functions which dynamically calculate the address of instructions 				   /////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/**
	 * @brief Dynamically calculate the target of direct CTI
	 *
	 * @param [in] _address The address of the call instruction 
	 * @param [out] _destAddress The target address of the instruction 
	 */
	void GetDirectCTIDest(ADDRESS _address, ADDRESS *_destAddress); 

	/**
	 * @brief Dynamically calculate both targets of conditional CTI
	 *
	 * @param [in] _address The address of the call instruction 
	 * @param [out] _destAddress The target addresses of the conditional jump 
	 */
	void GetConditionalCTIDest(ADDRESS _address, ADDRESS *_destAddress); 

	/**
	 * @brief Dynamically calculate the target of indirect CTI
	 *
	 * @param [in] _address The address of the call instruction 
	 * @param [out] _destAddress The target address of the instruction 
	 * @param [in] _context The context of the thread when the function is called 
	 */	
	void GetIndirectCTIDest(ADDRESS _address, ADDRESS *_destAddress, PCONTEXT _context);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////										Implemented in Utility.cpp												   /////////
	/////////			 				   		  debug utility print functions										     	   /////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	/**
	 * @brief The function that gets the information of a single instruction from Capstone library
	 *
	 * @param [in] address The address of the instruction 
	 * @param [out] instruction The pointer to instruction class that will be filled out 
	 * @return true if the insruction information is successfully read
	 */	
	bool GetOneInst(int address, Inst *instruction);

	/**
	 * @brief The function checks whether there is an instruction in a given address using Capstone library
	 *
	 * @param [in] address The address of the instruction 
	 * @return true if there is a valid insruction in the given address
	 */	
	bool IsValidInst(int address);

	/**
	 * @brief Gets the size of the instruction at the given address
	 *
	 * @param [in] The address of the instruction 
	 * @return The size of the instruction
	 */	
	int GetInstSize(ADDRESS address);

	/**
	 * @brief Print the given instruction to the given log file
	 *
	 * @param [in] address The address of the instruction that needs to be printed
	 * @param [in] _log_type The given log file
	 */
	void PrintInst(ADDRESS address, LogType _log_type);

	/**
	 * @brief Print the given n instructions to the given log file
	 *
	 * @param [in] address The address of the instructions that needs to be printed
	 * @param [in] _log_type The given log file
	 * @param [in] _size number of instructions that need to printed
	 */
	void PrintNInsts(ADDRESS address, LogType _log_type, int _size);

	/**
	 * @brief Print the details of a given instruction to the given log file
	 *
	 * @param [in] address The address of the instruction that needs to be printed
	 * @param [in] _log_type The given log file
	 */
	void PrintInstDetails(ADDRESS address, LogType _log_type);

	/** @brief Prints the instruction that are marked us discovered in the disassembly table */
	void PrintDisassembly();

private:

	/** The single unique object of this class */
	static Disassembler* s_instance;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////										Implemented in AddressTranslator.cpp									   /////////
	/////////			(1)	Series of helper functions which dynamically calculate the address of instructions 				   /////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	/**
	 * @brief Gets the dynamic value of the register given in the context
	 *
	 * @param [in] _num The number of the instruction to read its value 
	 * @param [in] _context The context of the thread when the function is called 
	 * @return int The dynamic value of the register given in the context
	 */
	int GetRegValue(int _num, PCONTEXT _context);
	
	/**
	 * @brief Gets the Reg value from Modrm bits
	 *
	 * @param [in] _modrm The modrm bits 
	 * @return uint8_t The number of register from Modrm
	 */
	uint8_t GetRegFromModrm(uint8_t _modrm);
	
	/**
	 * @brief Gets the Mod value from Modrm bits
	 *
	 * @param [in] _modrm The modrm bits 
	 * @return uint8_t The mod value from Modrm
	 */
	uint8_t GetModFromModrm(uint8_t _modrm);
	
	/**
	 * @brief Gets the Rm value from Modrm bits
	 *
	 * @param [in] _modrm The modrm bits 
	 * @return uint8_t The Rm value from Modrm
	 */
	uint8_t GetRmFromModrm(uint8_t _modrm);

	/** @brief unordered map containing the name of libcalls made */
	std::unordered_map<ADDRESS,std::string> libcalls;
};

#endif