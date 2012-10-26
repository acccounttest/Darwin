noinst_PROGRAMS = \
	as_m68k \
	as_m88k \
	as_i860 \
	as_ppc \
	as_ppc64 \
	as_hppa \
	as_sparc \
	as_i386 \
	as_x86_64 \
	as_arm 

# FIXME: this rule is exec'd at "make install" time to get
# AS-backends installed to the correct location. I found no
# better and clean way to do it using only Automake variables
install-exec-local:
	/bin/mkdir -p $(prefix)/${target_noncanonical}/libexec/gcc/darwin/m68k
	install -c -s -m 555 as_m68k $(prefix)/${target_noncanonical}/libexec/gcc/darwin/m68k/as
	/bin/mkdir -p $(prefix)/${target_noncanonical}/libexec/gcc/darwin/m88k
	install -c -s -m 555 as_m88k $(prefix)/${target_noncanonical}/libexec/gcc/darwin/m88k/as
	/bin/mkdir -p $(prefix)/${target_noncanonical}/libexec/gcc/darwin/i860
	install -c -s -m 555 as_i860 $(prefix)/${target_noncanonical}/libexec/gcc/darwin/i860/as
	/bin/mkdir -p $(prefix)/${target_noncanonical}/libexec/gcc/darwin/ppc
	install -c -s -m 555 as_ppc $(prefix)/${target_noncanonical}/libexec/gcc/darwin/ppc/as
	/bin/mkdir -p $(prefix)/${target_noncanonical}/libexec/gcc/darwin/ppc64
	install -c -s -m 555 as_ppc64 $(prefix)/${target_noncanonical}/libexec/gcc/darwin/ppc64/as
	/bin/mkdir -p $(prefix)/${target_noncanonical}/libexec/gcc/darwin/hppa
	install -c -s -m 555 as_hppa $(prefix)/${target_noncanonical}/libexec/gcc/darwin/hppa/as
	/bin/mkdir -p $(prefix)/${target_noncanonical}/libexec/gcc/darwin/sparc
	install -c -s -m 555 as_sparc $(prefix)/${target_noncanonical}/libexec/gcc/darwin/sparc/as
	/bin/mkdir -p $(prefix)/${target_noncanonical}/libexec/gcc/darwin/i386
	install -c -s -m 555 as_i386 $(prefix)/${target_noncanonical}/libexec/gcc/darwin/i386/as
	/bin/mkdir -p $(prefix)/${target_noncanonical}/libexec/gcc/darwin/x86_64
	install -c -s -m 555 as_x86_64 $(prefix)/${target_noncanonical}/libexec/gcc/darwin/x86_64/as
	/bin/mkdir -p $(prefix)/${target_noncanonical}/libexec/gcc/darwin/arm
	install -c -s -m 555 as_arm $(prefix)/${target_noncanonical}/libexec/gcc/darwin/arm/as
	ln -sv ../${target_noncanonical}/bin/as $(prefix)/bin/${target_noncanonical}-as

asbindir = ${prefix}/${target_noncanonical}/bin
asbin_PROGRAMS = \
	as

as_common_sources = \
	as.c \
	app.c \
	atof-generic.c \
	atof-ieee.c \
	expr.c \
	fixes.c \
	flonum-const.c \
	flonum-copy.c \
	flonum-mult.c \
	frags.c \
	hash.c \
	hex-value.c \
	input-file.c \
	input-scrub.c \
	layout.c \
	messages.c \
	obstack.c \
	read.c \
	sections.c \
	symbols.c \
	write_object.c \
	xmalloc.c \
	dwarf2dbg.c

as_m68k_SOURCES = \
	m68k.c \
	$(as_common_sources)

nodist_as_m68k_SOURCES = \
	apple_version.c

as_m88k_SOURCES = \
	m88k.c \
	$(as_common_sources)

nodist_as_m88k_SOURCES = \
	apple_version.c

as_i860_SOURCES = \
	i860.c \
	$(as_common_sources)

nodist_as_i860_SOURCES = \
	apple_version.c

as_i386_SOURCES = \
	i386.c \
	$(as_common_sources)

nodist_as_i386_SOURCES = \
	apple_version.c

as_x86_64_SOURCES = \
	$(as_i386_SOURCES)

nodist_as_x86_64_SOURCES = \
	apple_version.c

as_ppc_SOURCES = \
	ppc.c \
	$(as_common_sources)

nodist_as_ppc_SOURCES = \
	apple_version.c

as_ppc64_SOURCES = \
	$(as_ppc_SOURCES)

nodist_as_ppc64_SOURCES = \
	apple_version.c

as_hppa_SOURCES = \
	hppa.c \
	hppa-aux.c \
	$(as_common_sources)

nodist_as_hppa_SOURCES = \
	apple_version.c

as_sparc_SOURCES = \
	sparc.c \
	$(as_common_sources)

nodist_as_sparc_SOURCES = \
	apple_version.c

as_arm_SOURCES = \
	arm.c \
	$(as_common_sources)

nodist_as_arm_SOURCES = \
	apple_version.c

as_SOURCES = \
	driver.c

nodist_as_SOURCES = \
	apple_version.c

CLEANFILES = \
	apple_version.c

apple_version.c:
	echo "const char apple_version[]= " \"`vers_string -f cctools`\" ";" > $@

copts : cppflags arch-dependants passés en parm récursif

as_common_cflags = \
	-Os -g -Wall

as_common_cppflags = \
	-I../include \
	-DNeXT_MOD

as_common_ldadd = \
	-L../libstuff/ \
	-lstuff

as_m68k_CFLAGS = $(as_common_cflags)
as_m88k_CFLAGS = $(as_common_cflags)
as_i860_CFLAGS = $(as_common_cflags)
as_ppc_CFLAGS = $(as_common_cflags)
as_ppc64_CFLAGS = $(as_common_cflags)
as_hppa_CFLAGS = $(as_common_cflags)
as_sparc_CFLAGS = $(as_common_cflags)
as_i386_CFLAGS = $(as_common_cflags)
as_x86_64_CFLAGS = $(as_common_cflags)
as_arm_CFLAGS = $(as_common_cflags)
as_CFLAGS = $(as_common_cflags)

as_m68k_CPPFLAGS = $(as_common_cppflags) -DM68K -DBUILTIN_MMUS
as_m88k_CPPFLAGS = $(as_common_cppflags) -DM88K -Dm88110
as_i860_CPPFLAGS = $(as_common_cppflags) -DI860
as_ppc_CPPFLAGS = $(as_common_cppflags) -DPPC
as_ppc64_CPPFLAGS = $(as_common_cppflags) -DPPC -DARCH64
as_hppa_CPPFLAGS = $(as_common_cppflags) -DHPPA
as_sparc_CPPFLAGS = $(as_common_cppflags) -DSPARC
as_i386_CPPFLAGS = $(as_common_cppflags) -DI386 -Di486 -Di586 -Di686
as_x86_64_CPPFLAGS = $(as_common_cppflags) -DI386 -Di486 -Di586 -Di686 -DARCH64
as_arm_CPPFLAGS = $(as_common_cppflags) -DARM
as_CPPFLAGS = $(as_common_cppflags)

as_m68k_LDADD = $(as_common_ldadd) 
as_m88k_LDADD = $(as_common_ldadd) 
as_i860_LDADD = $(as_common_ldadd) 
as_ppc_LDADD = $(as_common_ldadd) 
as_ppc64_LDADD = $(as_common_ldadd) 
as_hppa_LDADD = $(as_common_ldadd) 
as_sparc_LDADD = $(as_common_ldadd) 
as_i386_LDADD = $(as_common_ldadd) 
as_x86_64_LDADD = $(as_common_ldadd) 
as_arm_LDADD = $(as_common_ldadd) 
as_LDADD = $(as_common_ldadd)
