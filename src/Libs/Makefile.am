
SUBDIRS =			\
	Types			\
	.				\
	Units			\
	InputPlugin		\
	OutputPlugin

#plugin library, logger and socks.
shared_LTLIBRARIES =			\
	liblogger.la				\
	libsocks.la					\
	libplugin.la

# Library to Log events.
liblogger_la_SOURCES =			\
	Logger.hpp					\
	Logger.cpp

# Library to use socks.
libsocks_la_SOURCES =			\
	Socks.hpp					\
	Socks.cpp

# Library used by input and output plugins to create new LCDSpicer2 plugins.
libplugin_la_SOURCES =			\
	Error.hpp					\
	Error.cpp					\
	GenericFunctions.hpp		\
	GenericFunctions.cpp		\
	Definitions.hpp				\
	Refresh.hpp					\
	Refresh.cpp					\
	Plugin.hpp					\
	Plugin.cpp

# Logger is used by plugins.
libplugin_la_LIBADD =			\
	$(top_srcdir)/src/Libs/Types/libvalue.la

#	liblogger.la				

libplugin_la_CXXFLAGS =	\
	-I./Types

pkginclude_HEADERS =			\
	Definitions.hpp				\
	Logger.hpp					\
	Socks.hpp					\
	Error.hpp					\
	Refresh.hpp					\
	Plugin.hpp

shareddir = $(libdir)/$(PACKAGE_TARNAME)