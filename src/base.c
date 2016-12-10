//***************************************************************************************
//
//! \file base.c
//! \Simple Define basic function for the whole project.
//
//! \author Sheng Yuan
//! \version 20161023
//! \date 2016-10-23
//! \copyright TCL
//
//***************************************************************************************/

#include "base.h"

// print string in red
#ifdef WIN32
void print_warning(const char * string)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
	printf(string);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

#else
void print_warning(const char * string)
{
	printf("%s\n", string);
}
#endif

// handle mis-input
void usage()
{
	print_warning("please enter as \"DVB-C.exe [ts-file]\"\n");
}

// combine two byes into a 16bit number
uint_16 byte_combine(uint_16 highbit, uint_16 lowbit)
{
	return (highbit << 8) | lowbit;
}

// output in markdown
void output()
{
	
}
