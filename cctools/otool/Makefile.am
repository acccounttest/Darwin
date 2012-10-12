bin_PROGRAMS = \
	otool

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

nodist_otool_SOURCES = \
	vers.c \
	ofile.c 

ofile.c:
	cp ../libstuff/$@ ./$@

vers.c:
	vers_string -c otool > $@

CLEANFILES = \
	ofile.c \
	vers.c

otool_CFLAGS = \
	-Os -g -Wall

otool_CPPFLAGS = \
	-I../include \
	-DEFI_SUPPORT \
	-D_MACH_I386_THREAD_STATUS_FPSTATE_LEGACY_FIELD_NAMES_ \
	-D_ARCHITECTURE_I386_FPU_FPSTATE_LEGACY_FIELD_NAMES_ \
	-DOTOOL

otool_LDADD = \
	-L../libstuff \
	-lstuff
