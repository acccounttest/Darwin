#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

m4_include(config/acx.m4)

AC_INIT([cctools], [800], [http://darwin.placeholder.fr/bugs.html])
AC_PREREQ([2.69])

AM_INIT_AUTOMAKE

ACX_NONCANONICAL_BUILD
ACX_NONCANONICAL_HOST
ACX_NONCANONICAL_TARGET

test "$host_noncanonical" = "$target_noncanonical" &&
  test "$program_prefix$program_suffix$program_transform_name" = \
          NONENONEs,x,x, &&
    program_transform_name=s,y,y,

# Checks for programs.
AC_PROG_CC
AC_PROG_INSTALL
AC_PROG_RANLIB
AM_PROG_CC_C_O

AC_CONFIG_FILES([Makefile
                 ar/Makefile
                 as/Makefile
                 cbtlibs/Makefile
                 efitools/Makefile
                 gprof/Makefile
                 include/Makefile
                 libstuff/Makefile
                 man/Makefile
                 misc/Makefile
                 otool/Makefile])
AC_OUTPUT
