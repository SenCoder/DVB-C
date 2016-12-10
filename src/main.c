//***************************************************************************************
//
//! \file main.c
//! \Simple This is a project for ts stream resolve.
//
//! \author Sheng Yuan
//! \version 20161023
//! \date 2016-10-23
//! \copyright TCL
//
//***************************************************************************************/

#include "ts.h"

int main(int argc, char** argv)
{
	if(argc != 2)
	{
		usage();
		exit(EXIT_FAILURE);
	}

	ts_stream_handler(argv[1]);
	
	return 0;
}

