AUTOMAKE_OPTIONS = foreign 
ACLOCAL_AMFLAGS = -I m4

CFLAGS = -Wall -pedantic
include_HEADERS = unicode-names.h

INCLUDES = @XFT_CFLAGS@

bin_PROGRAMS = unicode
unicode_SOURCES = unicode.c
unicode_LDADD = @XFT_LIBS@
