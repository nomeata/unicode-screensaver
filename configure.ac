# Process this file with autoconf to produce a configure script.

#AC_PREREQ(2.60)
AC_INIT(unicode-screensaver, 0.1, mail@joachim-breitner.de)
AC_CONFIG_SRCDIR([unicode.c])
AC_CONFIG_HEADER([config.h])
AC_CONFIG_MACRO_DIR([m4])
AM_INIT_AUTOMAKE

###############################################################################
#
#       Handle the --with-hackdir option
#
###############################################################################

have_hackdir=yes
with_hackdir_req=unspecified
AC_ARG_WITH(hackdir,[

Installation options:
  --with-hackdir=DIR      Where to install the hundreds of demo executables.
                          Default: PREFIX/libexec/xscreensaver/],
  [with_hackdir="$withval"; with_hackdir_req="$withval"],[with_hackdir=yes])

if test x"$with_hackdir" = xyes; then
  HACKDIR='${libexecdir}/xscreensaver'
elif test x"$with_hackdir" = xno; then
  HACKDIR='${bindir}'
else
  HACKDIR=$with_hackdir
fi

# canonicalize slashes.
HACKDIR=`echo "${HACKDIR}" | sed 's@/$@@;s@//*@/@g'`

# Expand HACKDIR as HACKDIR_FULL
HACKDIR_FULL=`eval eval eval eval eval eval eval eval eval echo $HACKDIR`

AC_SUBST(HACKDIR)
AC_SUBST(HACKDIR_FULL)

###############################################################################
#
#       Handle the --with-configdir option
#       Help for --with-x-app-defaults option added..
#
###############################################################################

have_configdir=yes
with_configdir_req=unspecified
AC_ARG_WITH(configdir,
[  --with-configdir=DIR    Where to install the data files that describe each
                          of the display modes to the GUI.
                          Default: PREFIX/share/xscreensaver/config/
],
  [with_configdir="$withval"; with_configdir_req="$withval"],
  [with_configdir=yes])

if test x"$with_configdir" = xyes; then
  HACK_CONF_DIR='${datadir}/xscreensaver/config'
elif test x"$with_configdir" = xno; then
  echo "error: must be yes, or a pathname: --with-configdir=$with_configdir"
  exit 1
else
  # there must be a better way than this...
  if test -z "`echo $with_configdir | sed 's@^/.*@@'`" ; then
    # absolute path
    HACK_CONF_DIR=$with_configdir
  else
    # relative path
    HACK_CONF_DIR="\${exec_prefix}$with_configdir"
  fi
fi




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
