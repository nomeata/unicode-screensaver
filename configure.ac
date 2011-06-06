# Process this file with autoconf to produce a configure script.

#AC_PREREQ(2.60)
AC_INIT(unicode-screensaver, 0.4, mail@joachim-breitner.de)
AC_CONFIG_SRCDIR([unicode.c])
AC_CONFIG_HEADER([config.h])
# AC_CONFIG_MACRO_DIR([m4])
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
AC_SUBST(HACKDIR)

###############################################################################
#
#       Handle the --with-desktopdir option
#
###############################################################################

have_desktopdir=yes
with_desktopdir_req=unspecified
AC_ARG_WITH(desktopdir,
[  --with-desktopdir=DIR   Where to install the hundreds of demo executables.
                          Default: PREFIX/share/applications/screensavers/],
  [with_desktopdir="$withval"; with_desktopdir_req="$withval"],[with_desktopdir=yes])

if test x"$with_desktopdir" = xyes; then
  DESKTOPDIR='${prefix}/share/applications/screensavers'
elif test x"$with_desktopdir" = xno; then
  echo "error: must be yes, or a pathname: --with-desktopdir=$with_desktopdir"
  exit 1
else
  DESKTOPDIR=$with_desktopdir
fi

# canonicalize slashes.
DESKTOPDIR=`echo "${DESKTOPDIR}" | sed 's@/$@@;s@//*@/@g'`
AC_SUBST(DESKTOPDIR)

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

AC_SUBST(HACK_CONF_DIR)



# Checks for programs.

###############################################################################
#
#       Function to figure out how to run the compiler.
#
###############################################################################

AC_DEFUN(AC_PROG_CC_ANSI,
 [AC_PROG_CC

  if test -z "$GCC"; then
    # not using GCC
    AC_MSG_CHECKING(how to request ANSI compilation)
    case "$host" in
      *-hpux* )
        AC_MSG_RESULT(HPUX: adding -Ae)
        CC="$CC -Ae"
      ;;
      *-aix* )
        AC_MSG_RESULT(AIX: adding -qlanglvl=ansi -qhalt=e)
        CC="$CC -qlanglvl=ansi -qhalt=e"
      ;;
      *-dec-* )
        AC_MSG_RESULT(DEC: adding -std1 -ieee)
        CC="$CC -std1"
      ;;
      *)
        AC_MSG_RESULT(no idea)
      ;;
    esac
  else
    # using GCC
    case "$host" in
      *-solaris*)
        AC_MSG_RESULT(Solaris: adding -D__EXTENSIONS__)
        CC="$CC -D__EXTENSIONS__"
      ;;
    esac
  fi

  OBJCC="$CC"

  AC_MSG_CHECKING([whether the compiler works on ANSI C])
  AC_TRY_RUN([ main(int ac, char **av) { return 0; } ],
     AC_MSG_RESULT(yes),
     AC_MSG_RESULT(no)
     AC_MSG_ERROR(Couldn't build even a trivial ANSI C program: check CC.),
     AC_MSG_ERROR(Couldn't build even a trivial ANSI C program: check CC.))

  if test -n "$GCC"; then
    AC_MSG_RESULT(Turning on gcc compiler warnings.)
    CC="$CC -pedantic -Wall -Wstrict-prototypes -Wnested-externs -Wmissing-prototypes"
    OBJCC="$OBJCC -Wall"
    # As of gcc 3.4, we have "-Wdeclaration-after-statement"
    # and so perhaps now we can do without -pedantic?
  else
    case "$host" in
      *-irix5* |*-irix6.[0-3]* )
        AC_MSG_RESULT(Turning on SGI compiler warnings.)
        CC="$CC -fullwarn -use_readonly_const -rdata_shared -g3"
      ;;
#     *-dec-osf* )
#       if test -z "$GCC"; then
#         AC_MSG_RESULT(Turning on DEC C compiler warnings.)
#         CC="$CC -migrate -w0 -verbose -warnprotos"
#       fi
#     ;;
    esac
  fi
])

###############################################################################
#
#       Check for availability of various gcc command-line options.
#
###############################################################################

AC_DEFUN(AC_CHECK_GCC_ARG,
 [if test -n "$GCC"; then
   AC_CACHE_CHECK([whether gcc accepts [$2]],
     ac_cv_gcc_accepts_[$1],
    [rm -rf conftest.$ac_ext
     touch conftest.$ac_ext
     if ( ( gcc -c [$2] conftest.$ac_ext -o/dev/null >/dev/null ) 2>&1 | \
          grep unrecognized >/dev/null ); then
       ac_cv_gcc_accepts_[$1]=no
     else
       ac_cv_gcc_accepts_[$1]=yes
       CC="$CC [$2]"
     fi])
   ac_gcc_accepts_[$1]="$ac_cv_gcc_accepts_[$1]"
  fi
])

AC_DEFUN(AC_NO_LONG_STRING_WARNINGS,
         [AC_CHECK_GCC_ARG(no_overlength, -Wno-overlength-strings)])

AC_DEFUN(AC_NO_MISPLACED_DECLARATIONS,
         [AC_CHECK_GCC_ARG(no_decl_after, -Wdeclaration-after-statement)])

AC_PROG_CC
AC_PROG_CC_ANSI
AC_NO_LONG_STRING_WARNINGS
AC_NO_MISPLACED_DECLARATIONS
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
