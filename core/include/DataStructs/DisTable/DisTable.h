/**
 * @file DisTable.h
 * @brief This file contains Funcs class which keeps the data structure for disassmebly table
 */

#ifndef _DIS_TABLE_H
#define _DIS_TABLE_H

#include "..\..\SubUnits\Utils\defs.h"
#include "..\..\SubUnits\Utils\RLBinUtils.h"

/**
 * @class DisTable
 * @brief class that keeps the data structure for disassmebly table
 */
class DisTable
{
public:
	/**
	 * @brief Creates the one and only instance of DisTable class
	 *
	 * @return DisTable* The pointer to the static DisTable object
	 */
	static DisTable* Create(void);

	/**
	 * @brief Gets the one and only instance of DisTable class
	 *
	 * @return DisTable* The pointer to the static DisTable object
	 */
	static DisTable* Get(void);

	/** Default destructor of the DisTable class */
	~DisTable(void);

	/** 
	 * @brief sets all the table entries to undiscovered 
	 *
	 * @param [in] _size The size of the table
	 */
	void Initialize(SIZE_TYPE _size);

	/** 
	 * @brief sets the entry at _address to _value 
	 *
	 * @param [in] _address The address of the entry to be set
	 * @param [in] _value The new value of the coresponding entry
	 */
	void SetEntry(ADDRESS _address, CELL _value);

	/** 
	 * @brief gets the entry at _address 
	 *
	 * @param [in] _address The address of the entry to be get
	 * @return CELL returns value of the entry at _address
	 */
	CELL GetEntry(ADDRESS _address);


private:
	/** size of the disassembly table */
	SIZE_TYPE size;
	
	/** table which is dynamic array of cell */
	CELL *table;

	/** The single unique object of this class */
	static DisTable* s_instance;
};

#endif