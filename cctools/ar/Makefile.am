arbindir = ${prefix}/${target_noncanonical}/bin
arbin_PROGRAMS = ar

install-exec-local:
	install -c -s -m 755 ar $(prefix)/bin/${target_noncanonical}-ar

uninstall-local:
	rm -f $(prefix)/bin/${target_noncanonical}-ar	

ar_SOURCES = \
	append.c \
	ar.c \
	archive.c \
	contents.c \
	delete.c \
	extract.c \
	misc.c \
	move.c \
	print.c \
	replace.c

noinst_HEADERS = \
	archive.h \
	extern.h \
	pathnames.h 	

nodist_ar_SOURCES = \
	vers.c

CLEANFILES =\
	vers.c

vers.c: 
	vers_string -c ar > $@

ar_CPPFLAGS = \
	-I$(top_srcdir)/include

ar_CFLAGS = \
	-g -Os -Wall

ar_LDADD = \
	-L$(top_builddir)/libstuff \
	-lstuff
