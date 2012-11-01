gprofbindir = ${prefix}/${target_noncanonical}/bin
gprofbin_PROGRAMS = \
	gprof

install-exec-local:
	install -c -s -m 755 gprof $(prefix)/bin/${target_noncanonical}-gprof

uninstall-local:
	rm -f $(prefix)/bin/${target_noncanonical}-gprof

gprof_SOURCES = \
	gprof.c \
	arcs.c \
	dfn.c \
	lookup.c \
	calls.c \
	hertz.c \
	printgprof.c \
	printlist.c \
	getnfile.c \
	scatter.c

noinst_HEADERS = \
	gprof.h \
	m68k.h \
	vax.h

nodist_gprof_SOURCES = \
	vers.c

vers.c:
	vers_string -c gprof > $@

CLEANFILES = vers.c

gprof_CFLAGS = \
	-Os -g -Wall

gprof_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-DNeXT_MOD \
	-DDEBUG

gprof_LDADD = \
	-L$(top_builddir)/libstuff \
	-lstuff
