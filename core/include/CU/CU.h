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
	 * @brief handles discovery of new code for a non-cti instruction
	 *
	 * param [in] The address of the instruction  
	 */
	void HandleNewDC(ADDRESS _address);

	/** 
	 * @brief handles discovery of new code for a non-cti instruction
	 *
	 * param [in] The address of the instruction  
	 */
	void HandleNewDJ(ADDRESS _address);

 	/** 
	 * @brief handles discovery of new code for a non-cti instruction
	 *
	 * param [in] The address of the instruction  
	 */
	void HandleNewIC(ADDRESS _address);

 	/** 
	 * @brief handles discovery of new code for a non-cti instruction
	 *
	 * param [in] The address of the instruction  
	 */
	void HandleNewIJ(ADDRESS _address);

 	/** 
	 * @brief handles discovery of new code for a non-cti instruction
	 *
	 * param [in] The address of the instruction  
	 */
	void HandleNewR(ADDRESS _address);
};

#endif