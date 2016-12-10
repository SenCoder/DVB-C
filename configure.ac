#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([DVB-C], [1.0], [yuansheng@tcl.com])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AC_CONFIG_SRCDIR([./src])

AC_CONFIG_FILES([
	src/Makefile
	Makefile
])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC

LIBS="-lm"

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([arpa/inet.h netinet/in.h stdlib.h string.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_CHECK_FUNCS([memset pow])

AC_OUTPUT
