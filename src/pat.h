//***************************************************************************************
//
//! \file pat.h
//! \Simple Delare basic function for PAT table handle.
//
//! \author Sheng Yuan
//! \version 20161023
//! \date 2016-10-23
//! \copyright TCL
//
//***************************************************************************************/

#ifndef _PAT_H
#define _PAT_H

#include "table.h"

//! the head length of pat table is 8B
#define PAT_HEAD_LEN 8

//! resolve pat table, called by table_info
void pat_table_info(const table * p_table);


#endif
