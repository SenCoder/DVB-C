//***************************************************************************************
//
//! \file section.h
//! \Simple Delare basic function for section handle.
//
//! \author Sheng Yuan
//! \version 20161023
//! \date 2016-10-23
//! \copyright TCL
//
//***************************************************************************************/

#ifndef _SECTION_H
#define _SECTION_H

#include "base.h"


/**
 * \brief initial a section.
 */

void section_init(section * p_sect, 
						const uint_8 * p_payload, 
						const uint_16 payload_size, 
						const uint_16 pid,
						table * p_table);


/**
 * \brief append payload to the current section.
 */
void section_append(section * p_sect, 
							const uint_8 * p_payload, 
							const uint_16 payload_size, 
							table * p_table);


/**
 * \brief release memory
 */
void section_destroy(section * p_sect);


#endif

