AUTOMAKE_OPTIONS = foreign 
ACLOCAL_AMFLAGS = -I m4

CFLAGS = -Wall -pedantic

AM_CPPFLAGS  = -I$(srcdir)/hacks -I$(srcdir)/utils @XFT_CFLAGS@ @X11_CFLAGS@ @FC_CFLAGS@ @XMU_CFLAGS@ @XT_CFLAGS@

hackexecdir = @HACKDIR@
desktopdir = @DESKTOPDIR@
hackconfdir = @HACK_CONF_DIR@

hackexec_PROGRAMS = unicode
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
	hacks/fps.h \
	hacks/fpsI.h \
	hacks/screenhack.h \
	hacks/screenhackI.h \
	utils/colors.h \
	utils/grabscreen.h \
	utils/hsv.h \
	utils/resources.h \
	utils/usleep.h \
	utils/utils.h \
	utils/visual.h \
	utils/vroot.h \
	utils/xmu.h \
	utils/yarandom.h
unicode_LDADD = @XFT_LIBS@ @X11_LIBS@ @FC_LIBS@ @XMU_LIBS@ @XT_LIBS@

nodist_desktop_DATA = unicode.desktop

unicode.desktop: unicode.desktop.in
	sed -e 's,[@]hackexecdir[@],$(hackexecdir),g' < $(srcdir)/unicode.desktop.in > unicode.desktop

dist_hackconf_DATA = unicode.xml

EXTRA_DIST = unicode.desktop.in

CLEANFILES = unicode.desktop
