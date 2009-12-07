AUTOMAKE_OPTIONS = foreign 
ACLOCAL_AMFLAGS = -I m4

CFLAGS = -Wall -pedantic

INCLUDES = -Ihacks -Iutils @XFT_CFLAGS@ @X11_CFLAGS@ @FC_CFLAGS@ @XMU_CFLAGS@ @XT_CFLAGS@

bin_PROGRAMS = unicode
unicode_SOURCES = \
	unicode.c \
	unicode-names.h \
	version.h \
	hacks/screenhack.c \
	utils/visual.c \
	utils/yarandom.c \
	utils/resources.c \
	utils/usleep.c \
	hacks/fps.c \
	hacks/*.h \
	utils/*.h
unicode_LDADD = @XFT_LIBS@ @X11_LIBS@ @FC_LIBS@ @XMU_LIBS@ @XT_LIBS@
