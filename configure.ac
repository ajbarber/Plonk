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
AC_PROG_LIBTOOL

# Checks for OpenGL libraries.

AX_CHECK_GL
AX_CHECK_GLU
AX_CHECK_GLUT

PKG_CHECK_MODULES([libpng], [libpng12], [HAVE_LIBPNG=yes], [HAVE_LIBPNG=no])
PKG_CHECK_MODULES([sfml], [sfml-all], [HAVE_SFML=yes], [HAVE_SFML=no])
PKG_CHECK_MODULES([glew], [glew], [HAVE_GLEW=yes], [HAVE_GLEW=no])
PKG_CHECK_MODULES([assimp], [assimp], [HAVE_ASSIMP=yes], [HAVE_ASSIMP=no])
PKG_CHECK_MODULES([glm], [glm], [HAVE_GLM=yes], [HAVE_GLM=no])
PKG_CHECK_MODULES([libsoil], [libsoil], [HAVE_SOIL=yes], [HAVE_SOIL=no])

if test \( "x$HAVE_GLEW" = xyes \) ; then
	AC_DEFINE(HAVE_GLEW, 1, [define to use glew]) 
fi

# CXXFLAGS="$CXXFLAGS $libpng_CFLAGS"
LIBS="$LIBS $libpng_LIBS $sfml_LIBS $glew_LIBS $assimp_LIBS"

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_OUTPUT(Makefile src/Makefile lib/soil/src/Makefile)

