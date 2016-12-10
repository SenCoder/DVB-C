//***************************************************************************************
//
//! \file pat.h
//! \Simple Define basic function for PAT table handle.
//
//! \author Sheng Yuan
//! \version 20161023
//! \date 2016-10-23
//! \copyright TCL
//
//***************************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "pat.h"
#include "section.h"

/**
 * @brief output the program_number, program map id in a pat table.
 * @param p_table is the address of table.
 */
void pat_table_info(const table * p_table)
{
	print_warning("====================== PAT ======================\n");
	int i = 0;
	section sec;
	
	for(; i < p_table->length; i ++)
	{
		sec = p_table->p_section[i];
		int j = 0;
		sec.curse += PAT_HEAD_LEN;
		while(sec.curse + 4 < sec.length)
		{
			uint_16 program_number = (uint_16)(sec.p_data[sec.curse]) << 8 | sec.p_data[sec.curse + 1];
			uint_16 program_map_pid = (uint_16)(sec.p_data[sec.curse + 2]) & 0x1f << 8 | sec.p_data[sec.curse + 3];
			if(program_number)
			{
				printf("program number = %d \t", program_number);
				printf("program map id = 0x%x \n", program_map_pid);
			}
			sec.curse += 4;
		}
	}
}

