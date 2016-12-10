//***************************************************************************************
//
//! \file ts_module_test.c
//! \Simple This file is for unit test.
//
//! \author Sheng Yuan
//! \version 20161023
//! \date 2016-10-28
//! \copyright TCL
//
//***************************************************************************************/


#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

void dvbc_first_test(void **state)
{
	(void) state;
}

int main(void) {
	
    const struct CMUnitTest tests[] = {
		
		cmocka_unit_test(dvbc_first_test),
	};
	
	return cmocka_run_group_tests(tests, NULL, NULL);
}
