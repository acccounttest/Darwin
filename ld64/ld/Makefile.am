ldbindir = ${prefix}/${target_noncanonical}/bin
ldbin_PROGRAMS = ld

install-exec-local:
	mkdir -p -m 755 $(prefix)/bin/
	install -c -s -m 755 ld $(prefix)/bin/${target_noncanonical}-ld 

uninstall-local:
	rm -f $(prefix)/bin/${target_noncanonical}-ld

ld_SOURCES = \
	InputFiles.cpp \
	Options.cpp \
	OutputFile.cpp \
	Resolver.cpp \
	SymbolTable.cpp \
	debugline.c \
	ld.cpp \
	parsers/archive_file.cpp \
	parsers/lto_file.cpp \
	parsers/macho_dylib_file.cpp \
	parsers/macho_relocatable_file.cpp \
	parsers/opaque_section_file.cpp \
	passes/branch_island.cpp \
	passes/branch_shim.cpp \
	passes/compact_unwind.cpp \
	passes/dtrace_dof.cpp \
	passes/dylibs.cpp \
	passes/got.cpp \
	passes/huge.cpp \
	passes/objc.cpp \
	passes/order_file.cpp \
	passes/stubs/stubs.cpp \
	passes/tlvp.cpp

nodist_ld_SOURCES = \
	ld_vers.c \
	configure.h

ld_vers.c:
	echo "const unsigned char ldVersionString[] = \"`vers_string ld`\";\n" > $@
	echo "const double ldVersionNumber __attribute__ ((used)) = (double) 0.;" >> $@

configure.h:
	echo "" > $@

# Dirty hack to ensure configure.h is generated before
# actual compilation of sources begins
Options.cpp: configure.h

CLEANFILES = \
	ld_vers.c \
	configure.h
	
ld_CFLAGS = \
	-g -Wall -O3

ld_CPPFLAGS = \
	-DLD_VERS=\"ld64\" -DNDEBUG \
	-I$(top_srcdir)/include/passes \
	-I$(top_srcdir)/include/passes/stubs \
	-I$(top_srcdir)/include/parsers \
	-I$(top_srcdir)/include \
	-I$(top_builddir)/${dyldinc} \
	-I$(top_builddir)/${cctoolsinc} \
	-I$(top_builddir)/${unwindinc}

ld_LDADD = \
	-lLTO
