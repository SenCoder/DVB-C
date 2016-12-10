//***************************************************************************************
//
//! \file ts.h
//! \Simple Delare basic function for ts packet handle.
//
//! \author Sheng Yuan
//! \version 20161023
//! \date 2016-10-23
//! \copyright TCL
//
//***************************************************************************************/


#ifndef _TS_H
#define _TS_H

#define TS_PACKET_LEN 188
#define FILE_SEARCH_SIZE TS_PACKET_LEN * 2 + 1

#include <stdio.h>
#include <stdlib.h>

#include "base.h"

/**
 * This is the structure of ts packet, which contains 4 Bytes.
 * The big endian and little endian should be considered.
 * This struct is not suggested to use any more.
 */
typedef struct ts_h  
{
	uint_8 syn_type;
	
	uint_8 PID_1:5;
	uint_8 transport_priority:1;
	uint_8 payload_unit_start_indicator:1;
	uint_8 transport_error_indicator:1;
	
	uint_8 PID_2;
	uint_8 continuity_counter:4;
	uint_8 adaption_field_control:2;
	uint_8 transport_scrambling_control:2;
	
} ts_header;


/**
 * \brief find the position of ts packet in ts file.
 * \param p_file the FILE * of .ts
 * \return the byte position of the first ts packet found.
 */
long search_ts_packet(FILE * p_file);


void ts_packet_handler(long ts_packet_pos, FILE * p_file, table_list * p_table_list);


/**
 * \brief get adaption field length of a ts packet
 * \param ts_header * p_ts_hd
 * \return the length of adaption field length, [0, 183]
 */
uint_8 get_adaption_field_len(ts_header * p_ts_hd);


void psi_resolve(table_list * const p_table_list, 
					const uint_16 pid, 
					const uint_8 * const p_payload, 
					const uint_8 payload_size,
					const uint_8 payload_unit_start_indicator);

/**
 * \brief The entry function for ts file resolve.
 * \param ts file name
 */
void ts_stream_handler(const char * ts_filename);

#endif
