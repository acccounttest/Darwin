toolsbindir = ${prefix}/${target_noncanonical}/bin
toolsbin_PROGRAMS = rebase unwinddump ObjectDump machocheck dyldinfo

install-exec-local:
	install -c -s -m 755 rebase $(prefix)/bin/${target_noncanonical}-rebase
	install -c -s -m 755 unwinddump $(prefix)/bin/${target_noncanonical}-unwinddump
	install -c -s -m 755 ObjectDump $(prefix)/bin/${target_noncanonical}-ObjectDump
	install -c -s -m 755 machocheck $(prefix)/bin/${target_noncanonical}-machocheck
	install -c -s -m 755 dyldinfo $(prefix)/bin/${target_noncanonical}-dyldinfo

uninstall-local:
	rm -f $(prefix)/bin/${target_noncanonical}-rebase
	rm -f $(prefix)/bin/${target_noncanonical}-unwinddump
	rm -f $(prefix)/bin/${target_noncanonical}-ObjectDump
	rm -f $(prefix)/bin/${target_noncanonical}-machocheck
	rm -f $(prefix)/bin/${target_noncanonical}-dyldinfo

rebase_SOURCES = rebase.cpp
rebase_CPPFLAGS = -I$(top_srcdir)/include -I$(top_builddir)/${cctoolsinc}

unwinddump_SOURCES = unwinddump.cpp
unwinddump_CPPFLAGS = -I$(top_srcdir)/include -I$(top_builddir)/${cctoolsinc}

ObjectDump_SOURCES = ObjectDump.cpp macho_relocatable_file.cpp lto_file.cpp debugline.c
ObjectDump_CPPFLAGS = -I$(top_srcdir)/include/parsers/ -I$(top_srcdir)/include \
	-I$(top_builddir)/${dyldinc} -I$(top_builddir)/${cctoolsinc} \
	-I$(top_builddir)/${unwindinc}
ObjectDump_LDADD = -lLTO

machocheck_SOURCES = machochecker.cpp
machocheck_CPPFLAGS = -I$(top_srcdir)/include -I$(top_builddir)/${cctoolsinc}

dyldinfo_SOURCES = dyldinfo.cpp
dyldinfo_CPPFLAGS = -I$(top_srcdir)/include -I$(top_builddir)/${cctoolsinc}
