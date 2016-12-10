//***************************************************************************************
//
//! \file table.h\c
//! \Simple Define basic function for table process.
//
//! \author Sheng Yuan
//! \version 20161023
//! \date 2016-10-23
//! \copyright TCL
//
//***************************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "table.h"
#include "section.h"
#include "nit.h"
#include "pat.h"


void table_list_init(table_list * p_table_list)
{
	p_table_list->size = TABLE_LIST_INIT_SIZE;
	p_table_list->length  = 0;
	p_table_list->p_table = (table *)malloc(sizeof(table) * p_table_list->size);
	if(!p_table_list->p_table)
	{
		printf("malloc fail, we will exit.\n");
		exit(EXIT_FAILURE);
	}
	memset(p_table_list->p_table, 0, p_table_list->size);
}


table * table_list_add(table_list * p_table_list, const uint_16 pid, const uint_8 table_id)
{
	table * p_table_to_ret = get_table(p_table_list, pid);
	if(p_table_to_ret)
	{
		return p_table_to_ret;
	}
	
	if(p_table_list->length >= p_table_list->size)
	{
		p_table_list->size += TABLE_LIST_SIZE_INCREASE;
		p_table_list->p_table = (table *)realloc(p_table_list->p_table, p_table_list->size * sizeof(table));
		if(p_table_list->p_table == NULL)
		{
			printf("realloc fail, we will exit.\n");
			exit(EXIT_FAILURE);
		}
	}

 	p_table_to_ret = & p_table_list->p_table[p_table_list->length ++];
	return table_init(p_table_to_ret, pid, table_id);
 	
}


table * get_table(table_list * p_table_list, const uint_16 pid)
{
	int i;
	for(i = 0; i < p_table_list->length; i ++)
	{
		if(pid == p_table_list->p_table[i].pid)
		{
			return & p_table_list->p_table[i];
		}
	}
	return NULL;
}


table * table_init(table * p_table, const uint_16 pid, const uint_8 table_id)
{
	p_table->length = 0;
	p_table->size = 0;
	p_table->pid = pid;
	p_table->table_id = table_id;
	return p_table;
}



//! add a section to the current table
section * table_add(table * p_table, const uint_8 section_number)
{
	if(p_table->length >= p_table->size)
	{
		p_table->size += TABLE_SIZE_INCREASE;
		p_table->p_section = (section *)realloc(p_table->p_section, p_table->size * sizeof(section));
		if(p_table->p_section == NULL)
		{
			printf("realloc fail, we will exit.\n");
			exit(EXIT_FAILURE);
		}
	}
	return & p_table->p_section[p_table->length ++];
	
}

section * get_section(table * p_table, const uint_8 section_number)
{
	int i;
	section * p_sec;
	for(i = 0; i < p_table->length; i ++)
	{
		p_sec = & p_table->p_section[i];
		if(section_number == p_sec->section_number)
		{
			return p_sec;
		}
	}
	return NULL;
}



/* Resolve information from table data */
void table_info(const table * p_table)
{
	switch(p_table->p_section[0].pid)
	{
		case NIT_PID:
			nit_table_info(p_table);
			break;
		case PAT_PID:
			pat_table_info(p_table);
			break;
		default:
			break;
	}
}

void all_table_info(const table_list * p_table_list)
{
	int i;
	for(i = 0; i < p_table_list->length; i ++)
	{
		table_info(& p_table_list->p_table[i]);
	}
}


void table_destroy(table * p_table)
{
	int i;
	for(i = 0; i < p_table->length; i ++)
	{
		section_destroy(& p_table->p_section[i]);
	}
	free(p_table->p_section);
}


void all_table_destroy(table_list * p_table_list)
{
	int i;
	for(i = 0; i < p_table_list->length; i ++)
	{
		table_destroy(& p_table_list->p_table[i]);
	}
	free(p_table_list->p_table);
}


