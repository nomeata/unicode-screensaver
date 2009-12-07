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

PKG_CHECK_MODULES(X11, x11)
AC_SUBST(X11_CFLAGS)
AC_SUBST(X11_LIBS)

PKG_CHECK_MODULES(XMU, xmu)
AC_SUBST(XMU_CFLAGS)
AC_SUBST(XMU_LIBS)

PKG_CHECK_MODULES(XT, xt)
AC_SUBST(XT_CFLAGS)
AC_SUBST(XT_LIBS)

PKG_CHECK_MODULES(XFT, xft)
AC_SUBST(XFT_CFLAGS)
AC_SUBST(XFT_LIBS)

PKG_CHECK_MODULES(FC, fontconfig)
AC_SUBST(FC_CFLAGS)
AC_SUBST(FC_LIBS)

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.


###############################################################################
#
#       Function to check whether gettimeofday() exists, and how to call it.
#       This may define HAVE_GETTIMEOFDAY and GETTIMEOFDAY_TWO_ARGS.
#
###############################################################################

AH_TEMPLATE([HAVE_GETTIMEOFDAY],
            [Define this if you have the gettimeofday function.])

AH_TEMPLATE([GETTIMEOFDAY_TWO_ARGS],
            [Define this if gettimeofday() takes two arguments.])

AC_DEFUN([AC_GETTIMEOFDAY_ARGS],
 [AC_MSG_CHECKING(how to call gettimeofday)
  AC_CACHE_VAL(ac_cv_gettimeofday_args,
   [AC_TRY_COMPILE([#include <stdlib.h>
                    #include <sys/time.h>],
                   [struct timeval tv; struct timezone tzp;
                    gettimeofday(&tv, &tzp);],
                   [ac_gettimeofday_args=2],
                   [AC_TRY_COMPILE([#include <stdlib.h>
                                    #include <sys/time.h>],
                                   [struct timeval tv; gettimeofday(&tv);],
                                   [ac_gettimeofday_args=1],
                                   [ac_gettimeofday_args=0])])
    ac_cv_gettimeofday_args=$ac_gettimeofday_args])
  ac_gettimeofday_args=$ac_cv_gettimeofday_args
  if test "$ac_gettimeofday_args" = 1 ; then
    AC_DEFINE(HAVE_GETTIMEOFDAY)
    AC_MSG_RESULT(one argument)
  elif test "$ac_gettimeofday_args" = 2 ; then
    AC_DEFINE(HAVE_GETTIMEOFDAY)
    AC_DEFINE(GETTIMEOFDAY_TWO_ARGS)
    AC_MSG_RESULT(two arguments)
  else
    AC_MSG_RESULT(unknown)
  fi
])

AC_GETTIMEOFDAY_ARGS

# Checks for library functions.

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
