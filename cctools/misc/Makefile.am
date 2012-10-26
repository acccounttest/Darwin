toolsbindir = ${prefix}/${target_noncanonical}/bin
toolsbin_PROGRAMS = \
	lipo \
	size \
	strings \
	nm \
	libtool \
	checksyms \
	indr \
	strip \
	nmedit \
	segedit \
	cmpdylib \
	pagestuff \
	redo_prebinding \
	seg_addr_table \
	check_dylib \
	seg_hack \
	install_name_tool \
	codesign_allocate \
	ctf_insert

install-exec-local:
	install -c -s -m 755 lipo $(prefix)/bin/${target_noncanonical}-lipo
	install -c -s -m 755 size $(prefix)/bin/${target_noncanonical}-size
	install -c -s -m 755 strings $(prefix)/bin/${target_noncanonical}-strings
	install -c -s -m 755 nm $(prefix)/bin/${target_noncanonical}-nm
	install -c -s -m 755 libtool $(prefix)/bin/${target_noncanonical}-libtool
	install -c -s -m 755 checksyms $(prefix)/bin/${target_noncanonical}-checksyms
	install -c -s -m 755 indr $(prefix)/bin/${target_noncanonical}-indr
	install -c -s -m 755 strip $(prefix)/bin/${target_noncanonical}-strip
	install -c -s -m 755 nmedit $(prefix)/bin/${target_noncanonical}-nmedit
	install -c -s -m 755 segedit $(prefix)/bin/${target_noncanonical}-segedit
	install -c -s -m 755 cmpdylib $(prefix)/bin/${target_noncanonical}-cmpdylib
	install -c -s -m 755 pagestuff $(prefix)/bin/${target_noncanonical}-pagestuff
	install -c -s -m 755 redo_prebinding $(prefix)/bin/${target_noncanonical}-redo_prebinding
	install -c -s -m 755 seg_addr_table $(prefix)/bin/${target_noncanonical}-seg_addr_table
	install -c -s -m 755 check_dylib $(prefix)/bin/${target_noncanonical}-check_dylib
	install -c -s -m 755 seg_hack $(prefix)/bin/${target_noncanonical}-seg_hack
	install -c -s -m 755 install_name_tool $(prefix)/bin/${target_noncanonical}-install_name_tool
	install -c -s -m 755 codesign_allocate $(prefix)/bin/${target_noncanonical}-codesign_allocate
	install	-c -s -m 755 ctf_insert $(prefix)/bin/${target_noncanonical}-ctf_insert

lib_LIBRARIES = \
	libredo_prebinding.a

# Common #

common_cflags = -Os -g -Wall
common_cppflags = -I../include -DLTO_SUPPORT -DTRIE_SUPPORT
common_ldadd = -L../libstuff -lstuff

# LIPO #

lipo_SOURCES = lipo.c
nodist_lipo_SOURCES = vers.c
lipo_CFLAGS = $(common_cflags)
lipo_CPPFLAGS = $(common_cppflags)
lipo_LDADD = $(common_ldadd)

# size #

size_SOURCES = size.c
nodist_size_SOURCES = vers.c
size_CFLAGS = $(common_cflags)
size_CPPFLAGS = $(common_cppflags)
size_LDADD = $(common_ldadd)

# strings #

strings_SOURCES = strings.c
nodist_strings_SOURCES = vers.c
strings_CFLAGS = $(common_cflags)
strings_CPPFLAGS = $(common_cppflags)
strings_LDADD = $(common_ldadd)

# NM #

nm_SOURCES = nm.c
nodist_nm_SOURCES = vers.c
nm_CFLAGS = $(common_cflags)
nm_CPPFLAGS = $(common_cppflags)
nm_LDADD = $(common_ldadd)

# libtool #

libtool_SOURCES = libtool.c
nodist_libtool_SOURCES = vers.c
libtool_CFLAGS = $(common_cflags)
libtool_CPPFLAGS = $(common_cppflags)
libtool_LDADD = $(common_ldadd)

# checksyms #

checksyms_SOURCES = checksyms.c
nodist_checksyms_SOURCES = vers.c
checksyms_CFLAGS = $(common_cflags)
checksyms_CPPFLAGS = $(common_cppflags)
checksyms_LDADD = $(common_ldadd)

# indr #

indr_SOURCES = indr.c
nodist_indr_SOURCES = vers.c
indr_CFLAGS = $(common_cflags)
indr_CPPFLAGS = $(common_cppflags)
indr_LDADD = $(common_ldadd)

# strip #

strip_SOURCES = strip.c
nodist_strip_SOURCES = vers.c
strip_CFLAGS = $(common_cflags)
strip_CPPFLAGS = $(common_cppflags) -I$(prefix)/include
strip_LDADD = $(common_ldadd) -L$(prefix)/lib -lprunetrie -lstdc++

# nmedit #

nmedit_SOURCES = strip.c
nodist_nmedit_SOURCES = vers.c
nmedit_CFLAGS = $(common_cflags)
nmedit_CPPFLAGS = $(common_cppflags) -DNMEDIT -I$(prefix)/include
nmedit_LDADD = $(common_ldadd)

# segedit #

segedit_SOURCES = segedit.c
nodist_segedit_SOURCES = vers.c
segedit_CFLAGS = $(common_cflags)
segedit_CPPFLAGS = $(common_cppflags)
segedit_LDADD = $(common_ldadd)

# cmpdylib #

cmpdylib_SOURCES = cmpdylib.c
nodist_cmpdylib_SOURCES = vers.c
cmpdylib_CFLAGS = $(common_cflags)
cmpdylib_CPPFLAGS = $(common_cppflags)
cmpdylib_LDADD = $(common_ldadd)

# pagestuff #

pagestuff_SOURCES = pagestuff.c
nodist_pagestuff_SOURCES = vers.c
pagestuff_CFLAGS = $(common_cflags)
pagestuff_CPPFLAGS = $(common_cppflags)
pagestuff_LDADD = $(common_ldadd)

# redo_prebinding #

redo_prebinding_SOURCES = redo_prebinding.c
nodist_redo_prebinding_SOURCES = vers.c
redo_prebinding_CFLAGS = $(common_cflags)
redo_prebinding_CPPFLAGS = $(common_cppflags)
redo_prebinding_LDADD = $(common_ldadd)

# seg_addr_table #

seg_addr_table_SOURCES = seg_addr_table.c
nodist_seg_addr_table_SOURCES = vers.c
seg_addr_table_CFLAGS = $(common_cflags)
seg_addr_table_CPPFLAGS = $(common_cppflags)
seg_addr_table_LDADD = $(common_ldadd)

# check_dylib #

check_dylib_SOURCES = check_dylib.c
nodist_check_dylib_SOURCES = vers.c
check_dylib_CFLAGS = $(common_cflags)
check_dylib_CPPFLAGS = $(common_cppflags)
check_dylib_LDADD = $(common_ldadd)

# seg_hack #

seg_hack_SOURCES = seg_hack.c
nodist_seg_hack_SOURCES = vers.c
seg_hack_CFLAGS = $(common_cflags)
seg_hack_CPPFLAGS = $(common_cppflags)
seg_hack_LDADD = $(common_ldadd)

# install_name_tool #

install_name_tool_SOURCES = install_name_tool.c
nodist_install_name_tool_SOURCES = vers.c
install_name_tool_CFLAGS = $(common_cflags)
install_name_tool_CPPFLAGS = $(common_cppflags)
install_name_tool_LDADD = $(common_ldadd)

# codesign_allocate #

codesign_allocate_SOURCES = codesign_allocate.c
nodist_codesign_allocate_SOURCES = vers.c
codesign_allocate_CFLAGS = $(common_cflags)
codesign_allocate_CPPFLAGS = $(common_cppflags)
codesign_allocate_LDADD = $(common_ldadd)
codesign_allocate_LDFLAGS = -sectcreate __TEXT __info_plist Info.plist

# ctf_insert #

ctf_insert_SOURCES = ctf_insert.c
nodist_ctf_insert_SOURCES = vers.c
ctf_insert_CFLAGS = $(common_cflags)
ctf_insert_CPPFLAGS = $(common_cppflags)
ctf_insert_LDADD = $(common_ldadd)

# libredo_prebinding_a #

libredo_prebinding_a_SOURCES = redo_prebinding.c
nodist_libredo_prebinding_a_SOURCES = vers.c
libredo_prebinding_a_CFLAGS = $(common_cflags)
libredo_prebinding_a_CPPFLAGS = $(common_cppflags) -DLIBRARY_API

vers.c:
	vers_string -c cctools_misc > $@
	echo "const char apple_version[]= " \"`vers_string -f cctools`\" ";" >> $@

CLEANFILES = vers.c
