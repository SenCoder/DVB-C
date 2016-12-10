//***************************************************************************************
//
//! \file table.h
//! \Simple Delare basic function for table process.
//
//! \author Sheng Yuan
//! \version 20161023
//! \date 2016-10-23
//! \copyright TCL
//
//***************************************************************************************/

#ifndef _TABLE_H
#define _TABLE_H

#include "base.h"

//! the initial size of table_list, which means how many tables the list can hold.
#define TABLE_LIST_INIT_SIZE 4
//! size add when the current size is not enough
#define TABLE_LIST_SIZE_INCREASE 2

//! the initial size of table, which means how many sections the table can hold.
#define TABLE_INIT_SIZE 1
//! size add when the current size is not enough
#define TABLE_SIZE_INCREASE 4


/**
 * \brief initial infomation in a table_list struct, and malloc memory.
 */
void table_list_init(table_list * p_table_list);


table * table_list_add(table_list * p_table_list, const uint_16 pid, const uint_8 table_id);


/**
 * \brief search the table in the table_list by pid.
 * \param p_table_list is the table_list address
 * \param pid is the pid of current table.
 * \return return section table if find, else return NULL.
 */
table * get_table(table_list * p_table_list, const uint_16 pid);


/**
 * \brief initial infomation in a table struct.
 */
table * table_init(table * p_table, const uint_16 pid, const uint_8 table_id);


section * table_add(table * p_table, const uint_8 section_number);


/**
 * \brief search the section in the table by pid
 * \param p_table is the table address
 * \param section_number is the section_number in section head.
 * \return return section address if find, else return NULL.
 */
section * get_section(table * p_table, const uint_8 section_number);


/**
 * \brief output all info in the table, called by all_table_info.
 * \param p_table is the table address
 */
void table_info(const table * p_table);


/**
 * @brief free all malloced memory in a table, called by all_table_destroy.
 */
void table_destroy(table * p_table);


/**
 * @brief output all info in every table.
 */
void all_table_info(const table_list * p_table_list);


/**
 * @brief free all malloced memory in a table list.
 */
void all_table_destroy(table_list * p_table_list);

#endif

