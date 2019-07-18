dnl Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([LCDSpicer2], [0.15.10.0], [http://sourceforge.net/tracker/?group_id=242109&atid=1118010],[lcdspicer2],[http://lcdspicer.sourceforge.net])
AC_COPYRIGHT([Copyright © 2015 - 2016 Patricio A. Rossi])
AC_CONFIG_SRCDIR([src/Libs/Logger.hpp])
AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE
AM_SILENT_RULES
AC_CONFIG_MACRO_DIR([m4])

dnl *******************
dnl * Needed Programs *
dnl *******************
AC_MSG_CHECKING([Programs])

AC_LANG([C++])
AC_PROG_CXX
AC_PROG_CPP
AX_CXX_COMPILE_STDCXX_11(noext, mandatory)
AC_PROG_AWK
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET
LT_INIT([disable-static])
AC_PROG_MKDIR_P

AC_ARG_ENABLE(
	[Documentation],
	[AS_HELP_STRING(
		[--disable-Documentation],
		[Disable the creation of developer's documentation]
	)]
)

AS_IF(
	[test "x$enable_Documentation" = "xno"],
	[AC_MSG_NOTICE([Documentation will not be created.])],
	[
	AC_MSG_NOTICE([Checking for programs to create developer's documentation])
	AC_CHECK_PROGS([DOXYGEN], [doxygen])
	AS_IF(
		[test -z "$DOXYGEN"],
		[AC_MSG_WARN([Doxygen not found - continuing without documentation support])],
		[]
	)]
)

AM_CONDITIONAL([HAVE_DOCUMENTATION], [test -n "$DOXYGEN"]) AM_COND_IF([HAVE_DOCUMENTATION], [AC_CONFIG_FILES([doc/lcdspicer2.doxyfile])])

#############
# LCDSpicer #
#############

AC_MSG_NOTICE([Checking for LCDSpicer2 dependencies])

PKG_CHECK_MODULES([LCDSPICER2], [tinyxml2 >= 2.2],
	echo -e "\ttinyxml2 ver `pkg-config --short-errors --modversion tinyxml2` found",
	AC_MSG_ERROR([tinyxml2 2.2 not found.])
)

dnl thread
AC_CHECK_LIB(pthread, pthread_create,
	[LCDSPICER2_LIBS+=" -lpthread"],
	AC_MSG_ERROR([You must have the thread development files installed to build.])
)

dnl dlopen
AC_CHECK_LIB([dl], [dlopen],
	[LCDSPICER2_LIBS+=" -ldl"],
	AC_MSG_ERROR([You must have the dl development files installed to build.])
)

dnl Checks for header files.
AC_CHECK_HEADERS(
	[syslog.h unistd.h fcntl.h netdb.h sys/ioctl.h utmpx.h],
	[],
	AC_MSG_ERROR([Headers syslog.h and unistd.h not found])
)

dnl Checks for library functions.
AC_CHECK_FUNCS([select socket strerror])

AC_SUBST(LCDSPICER2_LIBS)

#################
# Input Plugins #
#################
INPUT_PLUGINS_DIR="${libdir}/${PACKAGE_TARNAME}/plugins/input"
AC_SUBST(INPUT_PLUGINS_DIR)

dnl Users
AC_ARG_ENABLE(
	[Users],
	[AS_HELP_STRING(
		[--disable-Users],
		[Disable the input plugin Users]
	)]
)
AS_IF(
	[test "x$enable_Users" = "xno"],
	[AC_MSG_NOTICE([Plugin Users disabled.])],
	[
	AC_MSG_NOTICE([Checking for plugin Users dependencies])
	AC_CHECK_HEADERS(
		[utmpx.h pwd.h],
		[enable_Users=yes],
		[enable_Users=no]
		AC_MSG_WARN([Header utmpx.h or pwd.h not found unable to build input plugin Users])
	)]
)
AS_IF(
	[test "x$enable_Users" = "xyes"],
	[INPUT_PLUGINS+="Users "],
	[]
)
AM_CONDITIONAL([ENABLE_USERS],[test "x$enable_Users" = "xyes"])

dnl Calendar
AC_ARG_ENABLE(
	[Calendar],
	[AS_HELP_STRING(
		[--disable-Calendar],
		[Disable the input plugin Calendar]
	)],
	[AC_MSG_NOTICE([Plugin Calendar disabled.])
	enable_Calendar=no],
	[enable_Calendar=yes]
)
AS_IF(
	[test "x$enable_Calendar" = "xyes"],
	[INPUT_PLUGINS+="Calendar "],
	[]
)
AM_CONDITIONAL([ENABLE_CALENDAR],[test "x$enable_Calendar" = "xyes"])

dnl Kernel
AC_ARG_ENABLE(
	[Kernel],
	[AS_HELP_STRING(
		[--disable-Kernel],
		[Disable the input plugin Kernel]
	)],
	[AC_MSG_NOTICE([Plugin Kernel disabled.])
	enable_Kernel=no],
	[enable_Kernel=yes]
)
AS_IF(
	[test "x$enable_Kernel" = "xyes"],
	[INPUT_PLUGINS+="Kernel "],
	[]
)
AM_CONDITIONAL([ENABLE_KERNEL],[test "x$enable_Kernel" = "xyes"])

##################
# Output Plugins #
##################

OUTPUT_PLUGINS_DIR="${libdir}/${PACKAGE_TARNAME}/plugins/output"
AC_SUBST(OUTPUT_PLUGINS_DIR)

OUTPUT_PLUGINS_DATA_DIR="${datadir}/${PACKAGE_TARNAME}/output"
AC_SUBST(OUTPUT_PLUGINS_DATA_DIR)

dnl LogDumper (example output plugin).
AC_ARG_ENABLE(
	[LogDumper],
	[AS_HELP_STRING(
		[--enable-LogDumper],
		[Compiles the output plugin LogDumper]
	)],
	[enable_LogDumper=yes]
	[AC_MSG_NOTICE([Output plugin LogDumper enable.])],
	[enable_LogDumper=no]
)
AS_IF([test "x$enable_LogDumper" = "xyes"],
	OUTPUT_PLUGINS+="LogDumper ",
)
AM_CONDITIONAL([ENABLE_LOGDUMPER],[test "x$enable_LogDumper" = "xyes"])

dnl LCDProc.
AC_ARG_ENABLE(
	[LCDProc],
	[AS_HELP_STRING(
		[--disable-LCDProc],
		[Disable the output plugin LCDProc]
	)],
	[enable_LCDProc=no
	AC_MSG_NOTICE([Plugin Calendar disabled.])],
	[enable_LCDProc=yes]
)
AS_IF(
	[test "x$enable_LCDProc" = "xyes"],
	[OUTPUT_PLUGINS+="LCDProc "],
	[]
)
AM_CONDITIONAL([ENABLE_LCDPROC],[test "x$enable_LCDProc" = "xyes"])

AC_SUBST(OUTPUT_PLUGINS)
AC_SUBST(INPUT_PLUGINS)

dnl Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_INT8_T
AC_TYPE_INT16_T
AC_TYPE_INT32_T
AC_TYPE_INT64_T
AC_TYPE_SIZE_T
AC_TYPE_UINT8_T
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT64_T
AC_TYPE_SSIZE_T

dnl Checks for library functions.

AC_CONFIG_FILES([
	Makefile
	src/Makefile
	src/LCDSpicer2/Makefile
	src/Libs/Makefile
	src/Libs/Types/Makefile
	src/Libs/Units/Makefile
	src/Libs/InputPlugin/Makefile
	src/Libs/OutputPlugin/Makefile
	src/Plugins/Makefile
	src/Plugins/Input/Makefile
	src/Plugins/Input/Kernel/Makefile
	src/Plugins/Input/Users/Makefile
	src/Plugins/Input/Calendar/Makefile
	src/Plugins/Output/Makefile
	src/Plugins/Output/LogDumper/Makefile
	src/Plugins/Output/LCDProc/Makefile
	doc/Makefile
	examples/Makefile
])
AC_OUTPUT

dnl Dump the build configuration for the developer
echo -e "\n--------- build environment -----------
$PACKAGE_NAME: $PACKAGE_VERSION
WebSite      : $PACKAGE_URL

Build system : $build_cpu-$build_vendor-$build_os
C++ compiler : $CXX
Prefix       : $prefix
Configuration: $sysconfdir
CPPFLAGS     : ${CPPFLAGS}
CXXFLAGS     : ${CXXFLAGS}
Libraries    : ${LCDSPICER2_LIBS}
Linker       : $LD

Plugins
Output       : ${OUTPUT_PLUGINS}
Input        : ${INPUT_PLUGINS}"
