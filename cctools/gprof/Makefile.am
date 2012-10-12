bin_PROGRAMS = \
	gprof

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

nodist_gprof_SOURCES = \
	vers.c

vers.c:
	vers_string -c gprof > $@

CLEANFILES = vers.c

gprof_CFLAGS = \
	-Os -g -Wall

gprof_CPPFLAGS = \
	-I../include \
	-DNeXT_MOD \
	-DDEBUG

gprof_LDADD = \
	-L../libstuff \
	-lstuff
