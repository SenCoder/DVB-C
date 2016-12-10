//***************************************************************************************
//
//! \file nit.h
//! \Simple Delare basic function for NIT table handle.
//
//! \author Sheng Yuan
//! \version 20161023
//! \date 2016-10-23
//! \copyright TCL
//
//***************************************************************************************/

#ifndef _NIT_H
#define _NIT_H

#include "base.h" 
#include "table.h"
#include "section.h"


typedef struct cable_delivery_system_descriptor
{
	uint_8 tag;
	uint_8 length;

	uint_8 freq[4];
	uint_8 reserved;
	
	uint_8 :4;
	uint_8 fec_outer:4;
	
	uint_8 modulation;

	uint_8 symbol_rate_1[3];
	
	uint_8 fec_inner:4;
	uint_8 symbol_rate_2:4;
	
//	data;
}cds_descriptor;


//! get nit table from data, called by table_info
void nit_table_info(const table * p_table);

//! resolve cable delivery system descriptor
void cds_info(uint_8 * p_cds_data);


#endif
