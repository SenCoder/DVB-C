//***************************************************************************************
//
//! \file nit.c
//! \Simple Define basic function for NIT table handle.
//
//! \author Sheng Yuan
//! \version 20161023
//! \date 2016-10-23
//! \copyright TCL
//
//***************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "nit.h"


// get nit information from data
void nit_table_info(const table * p_table)
{
	print_warning("====================== NIT ======================\n");
	uint_8 i = 0;
	for(; i < p_table->length; i ++)
	{
		printf("================= NIT-Section-%d =================\n", i);
		printf("table_id = 0x%x \n", p_table->table_id);
		printf("pid = 0x%x \n", p_table->pid);

		section sec = p_table->p_section[i];
		printf("section_length = 0x%x \n", sec.length);
		printf("section_number = 0x%x \n", sec.section_number);
		
		sec.curse += 8;
		uint_16 ts_descriptor_len = 0;
		uint_16 network_descriptor_len = byte_combine(sec.p_data[sec.curse] & 0x0f, sec.p_data[sec.curse + 1]);
		sec.curse += 2 + network_descriptor_len + 2;
		while(sec.curse + 4 < sec.length)
		{
			sec.curse += 4;
			ts_descriptor_len = byte_combine(sec.p_data[sec.curse] & 0x0f, sec.p_data[sec.curse + 1]);
			sec.curse += 2;
			cds_info(sec.p_data + sec.curse);
			sec.curse += ts_descriptor_len;
		}
	}
}


void cds_info(uint_8 * p_cds_data)
{
	cds_descriptor * p_cds = (cds_descriptor *)(p_cds_data);
	printf("frequency: \t%x MHz\n", (uint_32)p_cds->freq[0] << 24 | (uint_32)p_cds->freq[1] << 16 | (uint_32)p_cds->freq[2] <<8 | (uint_32)p_cds->freq[3]);
	printf("modulation:\tQA%d \n", (int)pow(2.0, p_cds->modulation + 3));
	if(p_cds->fec_outer & 0x10 == 0x10)
		printf("FEC_outer: \tRS(204/188)\n");
	else
		printf("FEC_outer: \tunknown\n");
	printf("symbol_rate: \t%x%x%x%x Msymbol/s\n", p_cds->symbol_rate_1[0], p_cds->symbol_rate_1[1], p_cds->symbol_rate_1[2], p_cds->symbol_rate_2);
	printf("\n");
}


