AC_INIT([flashrom], [0.9.4-r1487], [flashrom@flashrom.org], [flashrom], [http://www.flashrom.org/])

AC_PREREQ(2.59)

AC_CANONICAL_TARGET

AC_CONFIG_SRCDIR([flashrom.c])
AM_INIT_AUTOMAKE([foreign])

# Internal (mainboard) flashing
AC_ARG_WITH([internal],
	    AC_HELP_STRING([--with-internal],[mainboard internal flashing support.]),
	    [internal="$withval"],[internal="yes"])

# Needs to be disabled on Windows.
AC_ARG_WITH([serprog],
	    AC_HELP_STRING([--with-serprog],[serprog support.]),
	    [serprog="$withval"],[serprog="yes"])

AC_ARG_WITH([linux_spi],
	    AC_HELP_STRING([--with-linux-spi],[Linux SPI subsystem support.]),
	    [linux_spi="$withval"],[linux_spi="no"])

AC_ARG_WITH([rayer_spi],
	    AC_HELP_STRING([--with-rayer-spi],[RayeR SPIPGM hardware support.]),
	    [rayer_spi="$withval"],[rayer_spi="yes"])

AC_ARG_WITH([nic3com],
	    AC_HELP_STRING([--with-nic3com],[3Com NICs support.]),
	    [nic3com="$withval"],[nic3com="yes"])

AC_ARG_WITH([gfxnvidia],
	    AC_HELP_STRING([--with-gfxnvidia],[NVIDIA graphics cards support. Note: write and erase do not work properly.]),
	    [gfxnvidia="$withval"],[gfxnvidia="yes"])

AC_ARG_WITH([satasii],
	    AC_HELP_STRING([--with-satasii],[SiI SATA controllers support.]),
	    [satasii="$withval"],[satasii="yes"])

AC_ARG_WITH([atahpt],
	    AC_HELP_STRING([--with-atahpt],[Highpoint (HPT) ATA/RAID controller support. IMPORTANT: This code is not yet working!]),
	    [atahpt="$withval"],[atahpt="no"])

AC_ARG_WITH([ft2232_spi],
	    AC_HELP_STRING([--with-ft2232-spi],[FT2232 SPI dongles support.]),
	    [ft2232_spi="$withval"],[ft2232_spi="yes"])

AC_ARG_WITH([dummy],
	    AC_HELP_STRING([--with-dummy],[dummy flashing support.]),
	    [dummy="$withval"],[dummy="yes"])

AC_ARG_WITH([drkaiser],
	    AC_HELP_STRING([--with-drkaiser],[Dr. Kaiser support.]),
	    [drkaiser="$withval"],[drkaiser="yes"])

AC_ARG_WITH([nicrealtek],
	    AC_HELP_STRING([--with-nicrealtek],[Realtek NICs support.]),
	    [nicrealtek="$withval"],[nicrealtek="yes"])

AC_ARG_WITH([nicnatsemi],
	    AC_HELP_STRING([--with-nicnatsemi],[National Semiconductor NICs support. Incomplete and untested.]),
	    [nicnatsemi="$withval"],[nicnatsemi="no"])

AC_ARG_WITH([nicintel],
	    AC_HELP_STRING([--with-nicintel],[Intel NICs support.]),
	    [nicintel="$withval"],[nicintel="yes"])

AC_ARG_WITH([nicintel_spi],
	    AC_HELP_STRING([--with-nicintel-spi],[SPI on Intel NICs support.]),
	    [nicintel_spi="$withval"],[nicintel_spi="yes"])

AC_ARG_WITH([gfxogp],
	    AC_HELP_STRING([--with-gfxogp],[The Open Graphics Project graphics card support.]),
	    [gfxogp="$withval"],[gfxogp="yes"])

AC_ARG_WITH([buspirate_spi],
	    AC_HELP_STRING([--with-buspirate-spi],[Bus Pirate SPI support.]),
	    [buspirate_spi="$withval"],[buspirate_spi="yes"])

AC_ARG_WITH([dediprog],
	    AC_HELP_STRING([--with-dediprog],[Dediprog SF100 support. Incomplete and untested.]),
	    [dediprog="$withval"],[dediprog="no"])

AC_ARG_WITH([satamv],
	    AC_HELP_STRING([--with-satamv],[Marvell SATA controllers support.]),
	    [satamv="$withval"],[satamv="yes"])

# Specific for Flashrom Wiki
AC_ARG_WITH([print_wiki],
	    AC_HELP_STRING([--with-print-wiki],[enable wiki export support. It is only useful if you have Flashrom wiki access.]),
	    [print_wiki="$withval"],[print_wiki="no"])

AC_C_BIGENDIAN(
	       [AC_DEFINE([__FLASHROM_BIG_ENDIAN__], [1], [Big endian])],
	       [AC_DEFINE([__FLASHROM_LITTLE_ENDIAN__], [1], [Little endian])],
	       [AC_MSG_ERROR([Unknown endianness])],
	       [AC_MSG_ERROR([No support for universal binaries yet])]
	       )

# Check for CPU-specific features
case $target_cpu in
	i386|i486|i586|i686|i786|x86_64)
		if test "$internal" = 'yes'; then
			enable_x86_only_internal="yes"
		fi
		;;
	mips*|power*)
		if test "$nic3com" = 'yes'; then
			AC_MSG_WARN([NIC 3Com is not supported for this target ($target_cpu). No PCI port I/O access on this architecture yet.])
			nic3com="no"
		fi
		if test "$nicnatsemi" = 'yes'; then
			AC_MSG_WARN([NIC NatSemi is not supported for this target ($target_cpu). No PCI port I/O access on this architecture yet.])
			nicnatsemi="no"
		fi
		if test "$nicrealtek" = 'yes'; then
			AC_MSG_WARN([NIC Realtek is not supported for this target ($target_cpu). No PCI port I/O access on this architecture yet.])
			nicrealtek="no"
		fi
		if test "$rayer_spi" = 'yes'; then
			AC_MSG_WARN([RayeR SPIPGM is not supported for this target ($target_cpu). No PCI port I/O access on this architecture yet.])
			rayer_spi="no"
		fi
		if test "$satamv" = 'yes'; then
			AC_MSG_WARN([Marvell SATA is not supported for this target ($target_cpu). No PCI port I/O access on this architecture yet])
			satamv="no"
		fi
		if test "$atahpt" = 'yes'; then
			AC_MSG_WARN([Highpoint (HPT) ATA/RAID controller support is not supported for this target ($target_cpu). No PCI port I/O access on this architecture yet.])
			atahpt="no"
		fi
		;;
	*)
		AC_MSG_ERROR([No support for this target ($target_cpu) yet])
		;;
esac

# Enable OS-specific compilation flags
# TODO

# Check whether we need seial support
if test "$serprog" = 'yes' -o \
	"$buspirate_spi" = 'yes' ; then
	serial="yes"
fi

# Check whether we need PCI support
if test "$internal" = 'yes' -o \
	"$rayer_spi" = 'yes' -o \
	"$nic3com" = 'yes' -o \
	"$gfxnvidia" = 'yes' -o \
	"$satasii" = 'yes' -o \
	"$atahpt" = 'yes' -o \
	"$drkaiser" = 'yes' -o \
	"$nicrealtek" = 'yes' -o \
	"$nicnatsemi" = 'yes' -o \
	"$nicintel" = 'yes' -o \
	"$nicintel_spi" = 'yes' -o \
	"$gfxogp" = 'yes' -o \
	"$satamv" = 'yes' ; then
	pci="yes"
fi

if test "$rayer_spi" = 'yes' -o \
	"$internal" = 'yes' -o \
	"$nicintel_spi" = 'yes' -o \
	"$gfxogp" = 'yes' ; then
	bitbang_spi="yes"
fi

# Checks for programs.
AC_PROG_CC
AC_PROG_INSTALL
AC_PROG_MAKE_SET

AC_PATH_PROG([DMIDECODE], dmidecode, [], [$PATH$PATH_SEPARATOR/usr/sbin])

# Checks for header files.
AC_CHECK_HEADERS([DirectIO/darwinio.h arpa/inet.h asm/sunddi.h fcntl.h inttypes.h limits.h machine/cpufunc.h machine/sysarch.h netdb.h netinet/in.h stddef.h stdint.h stdlib.h string.h strings.h sys/io.h sys/ioctl.h sys/psw.h sys/socket.h sys/sysi86.h sys/time.h sys/utsname.h termios.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_C_INLINE
AC_TYPE_OFF_T
AC_TYPE_SIZE_T
AC_CHECK_SIZEOF(int)
dnl mingw (for instance) lacks ssize_t
AC_CHECK_TYPE(ssize_t, int)
AC_CHECK_TYPE(uint8_t, unsigned char)
AC_CHECK_TYPE(uint16_t, unsigned short)
AC_CHECK_TYPE(uint64_t, unsigned long long)
if test $ac_cv_sizeof_int -eq 4 ; then
AC_CHECK_TYPE(uint32_t, unsigned int)
elif test $ac_cv_size_long -eq 4 ; then
AC_CHECK_TYPE(uint32_t, unsigned long)
else
AC_MSG_ERROR([no 32-bit type found])
fi

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_MMAP
AC_FUNC_REALLOC
AC_CHECK_FUNCS([gethostbyaddr gethostbyname getpagesize gettimeofday memmove memset munmap socket strcasecmp strchr strcspn strdup strerror strncasecmp strspn strstr strtol strtoul uname])

# Checks for pcilib
if test "$pci" = 'yes' ; then
	AC_CHECK_LIB([pci], [pci_alloc],,[AC_MSG_ERROR([pci library missing])])
fi

# check for socket (required for SunOS)
if test "$serprog" = 'yes' ; then
	AC_CHECK_LIB([socket], [socket])
fi

# Check for libusb
if test "$dediprog" = 'yes' -o "$ft2232_spi" = 'yes'  ; then
	AC_CHECK_LIB([usb], [usb_init])
fi

if test "$ft2232_spi" = 'yes' ; then
#	AC_CHECK_LIB([ftdi],[main],,[AC_MSG_ERROR([ftdi library missing which is required for ft2232-spi])])
	AC_CHECK_LIB([ftdi],[main],,[ft2232_spi="no"])
fi

# For Makefile.am
AM_CONDITIONAL(HAVE_INTERNAL, test "$internal" = "yes")
AM_CONDITIONAL(HAVE_DMIDECODE, test "$DMIDECODE" != "")
AM_CONDITIONAL(HAVE_X86_ONLY_INTERNAL, test "$enable_x86_only_internal" = "yes")
AM_CONDITIONAL(HAVE_SERPROG, test "$serprog" = "yes")
AM_CONDITIONAL(HAVE_LINUX_SPI, test "$linux_spi" = "yes")
AM_CONDITIONAL(HAVE_RAYER_SPI, test "$rayer_spi" = "yes")
AM_CONDITIONAL(HAVE_BITBANG_SPI, test "$bitbang_spi" = "yes")
AM_CONDITIONAL(HAVE_NIC3COM, test "$nic3com" = "yes")
AM_CONDITIONAL(HAVE_GFXNVIDIA, test "$gfxnvidia" = "yes")
AM_CONDITIONAL(HAVE_SATASII, test "$satasii" = "yes")
AM_CONDITIONAL(HAVE_ATAHPT, test "$atahpt" = "yes")
AM_CONDITIONAL(HAVE_FT2232_SPI, test "$ft2232_spi" = "yes")
AM_CONDITIONAL(HAVE_DUMMY, test "$dummy" = "yes")
AM_CONDITIONAL(HAVE_DRKAISER, test "$drkaiser" = "yes")
AM_CONDITIONAL(HAVE_NICREALTEK, test "$nicrealtek" = "yes")
AM_CONDITIONAL(HAVE_NICNATSEMI, test "$nicnatsemi" = "yes")
AM_CONDITIONAL(HAVE_NICINTEL, test "$nicintel" = "yes")
AM_CONDITIONAL(HAVE_NICINTEL_SPI, test "$nicintel_spi" = "yes")
AM_CONDITIONAL(HAVE_GFXOGP, test "$gfxogp" = "yes")
AM_CONDITIONAL(HAVE_BUSPIRATE_SPI, test "$buspirate_spi" = "yes")
AM_CONDITIONAL(HAVE_DEDIPROG, test "$dediprog" = "yes")
AM_CONDITIONAL(HAVE_SATAMV, test "$satamv" = "yes")
AM_CONDITIONAL(HAVE_SERIAL, test "$serial" = "yes")
AM_CONDITIONAL(HAVE_PCI, test "$pci" = "yes")
AM_CONDITIONAL(HAVE_PRINT_WIKI, test "$print_wiki" = "yes")

# FIXME remove in the future
AM_CONDITIONAL(HAVE_SYS_UTSNAME, test "$ac_cv_header_sys_utsname_h" = "yes")
AM_CONDITIONAL(HAVE_UNAME, test "$ac_cv_func_uname" = "yes")

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
