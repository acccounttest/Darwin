efibindir = ${prefix}/${target_noncanonical}/bin
efibin_PROGRAMS = \
	makerelocs \
	mtoc

install-exec-local:
	install -c -s -m 755 makerelocs $(prefix)/bin/${target_noncanonical}-makerelocs
	install -c -s -m 755 mtoc $(prefix)/bin/${target_noncanonical}-mtoc

uninstall-local:
	rm -f $(prefix)/bin/${target_noncanonical}-mtoc
	rm -f $(prefix)/bin/${target_noncanonical}-makerelocs

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
	-I$(top_srcdir)/include

makerelocs_LDADD = \
	-L$(top_builddir)/libstuff \
	-lstuff

mtoc_CFLAGS = \
	-Os -g -Wall

mtoc_CPPFLAGS = \
	-I$(top_srcdir)/include

mtoc_LDADD = \
	-L$(top_builddir)/libstuff \
	-lstuff
