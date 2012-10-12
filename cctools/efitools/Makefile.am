bin_PROGRAMS = \
	makerelocs \
	mtoc

makerelocs_SOURCES = \
	makerelocs.c

mtoc_SOURCES = \
	mtoc.c

nodist_makerelocs_SOURCES = \
	vers.c

nodist_mtoc_SOURCES = \
	vers.c

CLEANFILES = \
	vers.c

vers.c: 
	vers_string -c cctools_efi > $@
	echo "const char apple_version[]= " \"`vers_string -f cctools`\" ";" >> $@

makerelocs_CFLAGS = \
	-Os -g -Wall

makerelocs_CPPFLAGS = \
	-I../include

makerelocs_LDADD = \
	-L../libstuff \
	-lstuff

mtoc_CFLAGS = \
	-Os -g -Wall

mtoc_CPPFLAGS = \
	-I../include

mtoc_LDADD = \
	-L../libstuff \
	-lstuff
