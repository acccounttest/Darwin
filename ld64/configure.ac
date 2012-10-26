#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

m4_include(config/acx.m4)

AC_INIT([ld64], [123.2], [http://darwin.placeholder.fr/bugs.html])
AC_PREREQ([2.69])
AC_DISABLE_OPTION_CHECKING
AM_INIT_AUTOMAKE

ACX_NONCANONICAL_BUILD
ACX_NONCANONICAL_HOST
ACX_NONCANONICAL_TARGET

test "$host_noncanonical" = "$target_noncanonical" &&
  test "$program_prefix$program_suffix$program_transform_name" = \
          NONENONEs,x,x, &&
    program_transform_name=s,y,y,

unwindind=
cctoolsinc= 
dyldinc=

# FIXME:
# All those paths shouldn't be relative to PWD

AC_ARG_WITH([libunwind-include], 
            [AS_HELP_STRING([--with-libunwind-include=PATH],
                [Specify directory for installed libunwind include files])])

if test "x$with_libunwind_include" != x; then
    unwindinc="-I$PWD/$with_libunwind_include"
else
    AC_MSG_ERROR([Building LD64 requires libunwind headers.. Try the 
                  --with-libunwind-include option to specify its location. 
                  Source code for this package can be found at its owning site
                  as well as at http://github.com/LeoTestard/Darwin/])
fi

AC_ARG_WITH([cctools],
            [AS_HELP_STRING([--with-cctools=PATH],
                [Speficy directory for installed cctools package])])

if test "x$with_cctools" != x; then
    cctoolsinc="-I$PWD/$with_cctools/include"
else
    AC_MSG_ERROR([Building LD64 requires cctools. Try the --with-cctools option
                  to specify its location. Source code for this package can
                  be found at its owning site as well as at 
                  http://github.com/LeoTestard/Darwin/])
fi

AC_ARG_WITH([dyld],
            [AS_HELP_STRING([--with-dyld-include=PATH],
                [Specify directory for installed DYLD package])])

if test "x$with_dyld" != x; then
    dyldinc="-I$PWD/$with_dyld/include"
else
    AC_MSG_ERROR([Building LD64 requires DYLD. Try the --with-dyld option
                  to specify its location. Source code for this package can
                  be found at its owning site as well as at 
                  http://github.com/LeoTestard/Darwin/])
fi

AC_SUBST(unwindinc)
AC_SUBST(cctoolsinc)
AC_SUBST(dyldinc)

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AM_PROG_CC_C_O
AC_PROG_RANLIB

# Checks for libraries.

AC_CONFIG_FILES([Makefile
                 include/Makefile
                 ld/Makefile
                 libprunetrie/Makefile
                 man/Makefile
                 tools/Makefile])
AC_OUTPUT
