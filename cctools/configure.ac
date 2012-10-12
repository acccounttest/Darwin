#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])

AC_INIT([cctools], [800], [http://darwin.placeholder.fr/bugs.html])
AC_CONFIG_SRCDIR([libstuff/ofile.c])
AM_INIT_AUTOMAKE

# Checks for programs.
AC_PROG_CC
AC_PROG_INSTALL
AC_PROG_RANLIB
AM_PROG_CC_C_O

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([fcntl.h limits.h mach/mach.h paths.h stddef.h stdint.h stdlib.h string.h strings.h sys/file.h sys/param.h sys/time.h unistd.h utime.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_TYPE_UID_T
AC_C_INLINE
AC_TYPE_INT16_T
AC_TYPE_INT32_T
AC_TYPE_INT64_T
AC_FUNC_OBSTACK
AC_TYPE_OFF_T
AC_TYPE_SIZE_T
AC_TYPE_SSIZE_T
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT64_T
AC_TYPE_UINT8_T
AC_CHECK_TYPES([ptrdiff_t])

# Checks for library functions.
AC_FUNC_ALLOCA
AC_FUNC_CHOWN
AC_FUNC_ERROR_AT_LINE
AC_FUNC_FORK
AC_FUNC_MALLOC
AC_FUNC_MMAP
AC_FUNC_REALLOC
AC_CHECK_FUNCS([bzero fchdir ftruncate getpagesize gettimeofday memmove memset realpath strcasecmp strchr strerror strncasecmp strrchr strstr strtol strtoul utime])

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
