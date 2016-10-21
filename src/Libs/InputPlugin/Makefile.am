#Input plugins library.
shared_LTLIBRARIES =			\
	libinputplugin.la

# Library used by input plugins to create new LCDSpicer2 input plugins.
libinputplugin_la_SOURCES =		\
	InputDefinitions.hpp		\
	InputPlugin.hpp				\
	InputPlugin.cpp

# libplugins is used by input plugins.
libinputplugin_la_LIBADD =		\
	$(top_srcdir)/src/Libs/libplugin.la

libinputplugin_la_CXXFLAGS =	\
	-I..						\
	-I../Types

pkginclude_HEADERS =			\
	InputDefinitions.hpp		\
	InputPlugin.hpp

shareddir = $(libdir)/$(PACKAGE_TARNAME)