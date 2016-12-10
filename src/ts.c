//***************************************************************************************
//
//! \file ts.c
//! \Simple Define basic function for ts packet handle.
//
//! \author Sheng Yuan
//! \version 20161023
//! \date 2016-10-23
//! \copyright TCL
//
//***************************************************************************************/

#include "ts.h"
#include "section.h"
#include "table.h"


/* Entry function for ts file */
void ts_stream_handler(const char * ts_filename)
{
	FILE * pfile = fopen(ts_filename, "rb");
	if(pfile == NULL)
	{
		print_warning("file read fail, please check if the file is in current directory.\n");
		exit(EXIT_FAILURE);
	}
	table_list psi_table_list;
	table_list_init(& psi_table_list);
	
	long pos = search_ts_packet(pfile);
	if(pos >= 0)
	{
		ts_packet_handler(pos, pfile, & psi_table_list);
	}
	fclose(pfile);
	
	all_table_info(& psi_table_list);
	all_table_destroy(& psi_table_list);
}


/* find the position of ts packet in ts stream. */
long search_ts_packet(FILE * p_file)
{
	// search for 0x47 to get the position of ts stream.
	uint_8 * p_ts_label = (uint_8 *)malloc(sizeof(uint_8) * (TS_PACKET_LEN * 2 + 1));
	long curse = 0;
	if(p_ts_label == NULL)
	{
		fprintf(stderr, "malloc fail\n");
		exit(EXIT_FAILURE);
	}
	while(p_ts_label[0] != 0x47 || p_ts_label[TS_PACKET_LEN] != 0x47 || p_ts_label[TS_PACKET_LEN*2] != 0x47)
	{
		uint_16 read_size = fread(p_ts_label, sizeof(uint_8), FILE_SEARCH_SIZE, p_file);
		if(read_size < FILE_SEARCH_SIZE)
		{
			printf("No ts stream found \n");
			free(p_ts_label);
			return -1;
		}
		else if(p_ts_label[0] == 0x47 && p_ts_label[TS_PACKET_LEN] == 0x47 && p_ts_label[TS_PACKET_LEN*2] == 0x47)
		{
			// ts stream found.
			free(p_ts_label);
			printf("ts packet found at %d B\n", (int)curse);
			return curse;
		}
		fseek(p_file, ++ curse , SEEK_SET);
	}
	free(p_ts_label);
	return -1;
}


/* get adaption field length */
uint_8 get_adaption_field_len(ts_header * p_ts_hd)
{
	switch(p_ts_hd->adaption_field_control)
	{
		case 0: // reserved
			return 0;
			break;
		case 1: // payload
			return 0;
			break;
		default: // payload and adaption
			return ((uint_8 *)p_ts_hd)[4] + 1;
			break;
	}
}


/**
 * resolve infomation in ts packet
 */
void ts_packet_handler(long ts_packet_pos, FILE * p_file, table_list * p_table_list)
{
	uint_8 * p_ts_packet = (uint_8*) malloc (sizeof(uint_8) * TS_PACKET_LEN);
	ts_header * p_ts_hd = NULL;
	if(p_ts_packet == NULL)
	{
		fprintf(stderr, "malloc fail\n");
		exit(EXIT_FAILURE);
	}
	fseek(p_file, ts_packet_pos, SEEK_SET);
	while(fread(p_ts_packet, sizeof(uint_8), TS_PACKET_LEN, p_file) > 0)
	{
		p_ts_hd = (ts_header *)p_ts_packet;
		// 4B ts header + adaption field length + 1B/0B pointer_field
		
		uint_8 offset = 4 + get_adaption_field_len(p_ts_hd) + p_ts_hd->payload_unit_start_indicator;
		uint_8 payload_size = TS_PACKET_LEN - offset;
		uint_8 * p_payload = p_ts_packet + offset;
		uint_16 pid = byte_combine(p_ts_hd->PID_1, p_ts_hd->PID_2);
		
		if(pid == NIT_PID || pid == PAT_PID)
		{
			psi_resolve(p_table_list, pid, p_payload, payload_size, p_ts_hd->payload_unit_start_indicator);
		}
		
		ts_packet_pos += TS_PACKET_LEN;
		fseek(p_file, ts_packet_pos, SEEK_SET);
	}
	free(p_ts_packet);
}

/**
 * \brief resolve payload of a ts packet
 */
void psi_resolve(table_list * const p_table_list, 
					const uint_16 pid, 
					const uint_8 * const p_payload, 
					const uint_8 payload_size,
					const uint_8 payload_unit_start_indicator)
{
	table * p_table = table_list_add(p_table_list, pid, p_payload[0]);
	if(payload_unit_start_indicator && ! get_section(p_table, p_payload[6]))
	{
		section_init(table_add(p_table, p_payload[6]), p_payload, payload_size, pid, p_table);
	}
	else
	{
		section_append(& p_table->p_section[p_table->length - 1], p_payload, payload_size, p_table);
	}
	
}


