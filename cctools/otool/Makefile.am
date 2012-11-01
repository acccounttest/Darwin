otoolbindir = ${prefix}/${target_noncanonical}/bin
otoolbin_PROGRAMS = \
	otool

install-exec-local:
	install -c -s -m 755 otool $(prefix)/bin/${target_noncanonical}-otool

uninstall-local:
	rm -f $(prefix)/bin/${target_noncanonical}-otool

otool_SOURCES = \
	main.c \
	ofile_print.c \
	m68k_disasm.c \
	i860_disasm.c \
	m88k_disasm.c \
	i386_disasm.c \
	ppc_disasm.c \
	hppa_disasm.c \
	sparc_disasm.c \
	print_objc.c \
	notify.c \
	arm_disasm.c \
	print_objc2_64bit.c \
	print_objc2_32bit.c \
	coff_print.c

noinst_HEADERS = \
	arm_disasm.h \
  	hppa_disasm.h \
   	i386_disasm.h \
   	i860_disasm.h \
   	m68k_disasm.h \
   	m88k_disasm.h \
   	notify.h \
	ofile_print.h \
   	otool.h \
	ppc_disasm.h \
	sparc_disasm.h

nodist_otool_SOURCES = \
	vers.c

vers.c:
	vers_string -c otool > $@

CLEANFILES = \
	ofile.c \
	vers.c

otool_CFLAGS = \
	-Os -g -Wall

otool_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-DEFI_SUPPORT \
	-D_MACH_I386_THREAD_STATUS_FPSTATE_LEGACY_FIELD_NAMES_ \
	-D_ARCHITECTURE_I386_FPU_FPSTATE_LEGACY_FIELD_NAMES_ \
	-DOTOOL

otool_LDADD = \
	-L$(top_builddir)/libstuff \
	-lstuff
