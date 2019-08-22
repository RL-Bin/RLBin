/**
 * @file CU.h
 * @brief This file contains CU class which controls and manages all other core classes
 */

#ifndef _CU_H
#define _CU_H

#include "..\SubUnits\Utils\defs.h"
#include "..\SubUnits\Utils\RLBinUtils.h"

/**
 * @class CU
 * @brief class that manages and controls all other core modules
 */
class CU
{
public:
	/** @brief Creates the single instance of the CU class */
	static CU* Create(void);

	/** @brief gets the single instance of the CU class */
	static CU* Get(void);

	/** @brief initializes all other modules*/
	void Initialize(void);

	/** @brief finalizes all other modules*/
	void Finalize(void);

	/** 
	 * @brief handles discovery of new code
	 *
	 * param [in] p The pointer to the exception structure  
	 */
	void HandleNewCode(PEXCEPTION_POINTERS p);

	/** 
	 * @brief handles checking targets of indirect CTIs
	 *
	 * param [in] p The pointer to the exception structure  
	 */
	void HandleRecurringCheck(PEXCEPTION_POINTERS p);

	/** brief count the number of times exception handler is called */
	int counter;

private:	
	/** The single unique object of this class */
	static CU* s_instance;

	/** 
	 * @brief handles discovery of new code for a non-cti instruction
	 *
	 * param [in] The address of the instruction  
	 */
	void HandleNewNC(ADDRESS _address);

	/** 
	 * @brief handles discovery of new code for a direct call instruction
	 *
	 * param [in] The address of the instruction  
	 */
	void HandleNewDC(ADDRESS _address);

	/** 
	 * @brief handles discovery of new code for a direct jump instruction
	 *
	 * param [in] The address of the instruction  
	 */
	void HandleNewDJ(ADDRESS _address);

 	/** 
	 * @brief handles discovery of new code for an indirect call or jump instruction
	 *
	 * param [in] The address of the instruction  
	 * param [in] The target of the call or jump instruction  
	 * param [in] The next address after external jump or call
	 */
	void HandleNewICJ(ADDRESS _address, ADDRESS _cj_address, ADDRESS _next_inst);

 	/** 
	 * @brief handles discovery of new code for a return instruction
	 *
	 * param [in] The address of the instruction  
	 * param [in] The return address   
	 */
	void HandleNewR(ADDRESS _address,ADDRESS _return_address);
};

#endif