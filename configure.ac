#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT(plonk, 1.00,aj_barber@yahoo.com.au)
AM_INIT_AUTOMAKE(plonk,1.0)
AC_CONFIG_SRCDIR([src/main.cpp])
AC_CONFIG_MACRO_DIR([m4])
# AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CXX

# Checks for OpenGL libraries.

AX_CHECK_GL
AX_CHECK_GLU
AX_CHECK_GLUT

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_OUTPUT(Makefile src/Makefile)

