#Output plugins library.
shared_LTLIBRARIES =			\
	liboutputplugin.la

# Library used by output plugins to create new LCDSpicer2 output plugins.
liboutputplugin_la_SOURCES =	\
	OutputDefinitions.hpp		\
	Widget.hpp					\
	Widget.cpp					\
	TextWidget.hpp				\
	TextWidget.cpp				\
	BarWidget.hpp				\
	BarWidget.cpp				\
	ClockWidget.hpp				\
	ClockWidget.cpp				\
	Screen.cpp					\
	Screen.hpp					\
	OutputPlugin.hpp			\
	OutputPlugin.cpp

# Libs used by output plugins.
liboutputplugin_la_LIBADD =				\
	$(top_srcdir)/src/Libs/Types/libtypes.la \
	$(top_srcdir)/src/Libs/libplugin.la

liboutputplugin_la_CXXFLAGS =	\
	-I..						\
	-I../Types

pkginclude_HEADERS =			\
	OutputDefinitions.hpp		\
	OutputPlugin.hpp			\
	Widget.hpp					\
	TextWidget.hpp				\
	BarWidget.hpp				\
	ClockWidget.hpp				\
	Screen.hpp

shareddir = $(libdir)/$(PACKAGE_TARNAME)