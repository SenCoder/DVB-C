//***************************************************************************************
//
//! \file base.h
//! \Simple Declare basic structure and function for the whole project.
//
//! \author Sheng Yuan
//! \version 20161023
//! \date 2016-10-23
//! \copyright TCL
//
//***************************************************************************************/
#ifndef _BASE_H
#define _BASE_H

#include <stdio.h>

#ifdef WIN32
	#include <windows.h>
#endif

#ifdef __linux
	#include <arpa/inet.h>
	#include <netinet/in.h>
#endif

#ifndef BIG_ENDIAN
	#define BIG_ENDIAN
#endif

#define PAT_PID 0x00
#define NIT_PID 0x10

#define PAT_TABLE_ID 0x00
#define NIT_TABLE_ID 0x40


typedef unsigned int uint_32;
typedef unsigned short uint_16;
typedef unsigned char uint_8;

/**
 * general section for different packets.
 */ 
typedef struct sect
{
	uint_16 pid;
	uint_8 section_number;
	uint_16 length;
	uint_16 curse;
	uint_8 is_over;
	uint_8* p_data;
} section;


/**
 * the general_table is applied to PAT, NIT .etc, all table structure.
 */

typedef struct general_table
{
	uint_8 size;
	uint_8 length;
	uint_16 pid;
	uint_8 table_id;
	section * p_section;
} table;


/**
 * table_list is a linear list which contains multi tables.
 */

typedef struct list_table
{
	uint_8 size;
	uint_8 length;
	table * p_table;
} table_list;


//! handle mis-input.
void usage();

//! print string in red.
void print_warning(const char * string);

//! combine two byes to a 16bit number, not advised to use.
uint_16 byte_combine(uint_16 highbit, uint_16 lowbit);

#endif
