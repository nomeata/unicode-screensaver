# Process this file with autoconf to produce a configure script.

#AC_PREREQ(2.60)
AC_INIT(unicode-screensaver, 0.1, mail@joachim-breitner.de)
AC_CONFIG_SRCDIR([unicode.c])
AC_CONFIG_HEADER([config.h])
AC_CONFIG_MACRO_DIR([m4])
AM_INIT_AUTOMAKE

# Checks for programs.
AC_PROG_CC
AC_PROG_INSTALL
AC_PROG_MAKE_SET

# Checks for libraries.
AM_PROG_LIBTOOL

PKG_CHECK_MODULES(XFT, xft)
AC_SUBST(XFT_CFLAGS)
AC_SUBST(XFT_LIBS)

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
