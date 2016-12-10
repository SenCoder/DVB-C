//***************************************************************************************
//
//! \file section.c
//! \Simple Define basic function for section handle.
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

#include "section.h"


void section_init(section * p_sect, 
					const uint_8 * p_payload, 
					const uint_16 payload_size, 
					const uint_16 pid, 
					table * p_table)
{
	p_sect->pid = pid;
	p_sect->curse = 0;
	p_sect->is_over = 0;
	p_sect->length = ((uint_16)p_payload[1] & 0x0f) << 8 | (uint_16)p_payload[2];
	p_sect->section_number = p_payload[6];
	
	p_sect->p_data = (uint_8 *)malloc(sizeof(uint_8) * p_sect->length);
	if(p_sect->p_data == NULL)
	{
		printf("malloc fail, we will exit.\n");
		exit(EXIT_FAILURE);
	}
	section_append(p_sect, p_payload, payload_size, p_table);
}


void section_append(section * p_sect, 
					const uint_8 * p_payload, 
					const uint_16 payload_size, 
					table * p_table)
{
	if(payload_size + p_sect->curse > p_sect->length)
	{
		memcpy(p_sect->p_data + p_sect->curse, p_payload, p_sect->length - p_sect->curse);
		p_sect->curse = 0;
		p_sect->is_over = 1;
	}
	else if(! p_sect->is_over)
	{
		memcpy(p_sect->p_data + p_sect->curse, p_payload, payload_size);
		p_sect->curse += payload_size;
	}
}


void section_destroy(section * p_sect)
{
	free(p_sect->p_data);
}


