noinst_LIBRARIES = \
	libstuff.a \
	libstuff_p.a

libstuff_common_sources = \
	allocate.c \
	errors.c \
	arch.c \
	execute.c \
	bytesex.c \
	coff_bytesex.c \
	rnd.c \
	hppa.c \
	swap_headers.c \
	reloc.c \
	version_number.c \
	get_toc_byte_sex.c \
	best_arch.c \
	fatals.c \
	arch_usage.c \
	ofile.c \
	ofile_error.c \
	print.c \
	set_arch_flag_name.c \
	seg_addr_table.c \
	dylib_table.c \
	breakout.c \
	writeout.c \
	checkout.c \
	fatal_arch.c \
	ofile_get_word.c \
	vm_flush_cache.c \
	hash_string.c \
	dylib_roots.c \
	guess_short_name.c \
	SymLoc.c \
	get_arch_from_host.c \
	crc32.c \
	macosx_deployment_target.c \
	symbol_list.c \
	unix_standard_mode.c \
	lto.c 

libstuff_a_SOURCES = \
	$(libstuff_common_sources)

libstuff_p_a_SOURCES = \
	$(libstuff_common_sources)

libstuff_common_cflags = \
	-Os -g

libstuff_common_cppflags = \
	-DLTO_SUPPORT \
	-D_MACH_I386_THREAD_STATUS_FPSTATE_LEGACY_FIELD_NAMES_ \
	-D_ARCHITECTURE_I386_FPU_FPSTATE_LEGACY_FIELD_NAMES_ \
	-I$(top_srcdir)/include/

libstuff_a_CFLAGS = $(libstuff_common_cflags)
libstuff_a_CPPFLAGS = $(libstuff_common_cppflags)
libstuff_p_a_CFLAGS = $(libstuff_common_cflags) -pg
libstuff_p_a_CPPFLAGS = $(libstuff_common_cppflags)
