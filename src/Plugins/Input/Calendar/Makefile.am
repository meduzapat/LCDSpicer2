## Process this file with automake to produce Makefile.in

if ENABLE_CALENDAR

inputpluginsdir = $(INPUT_PLUGINS_DIR)

inputplugins_LTLIBRARIES =	\
	Calendar.la

Calendar_la_SOURCES =		\
	Calendar.hpp			\
	Calendar.cpp

Calendar_la_CXXFLAGS =				\
	-I$(top_srcdir)/src/Libs		\
	-I$(top_srcdir)/src/Libs/Types	\
	-I$(top_srcdir)/src/Libs/InputPlugin

Calendar_la_LDFLAGS =		\
	-module					\
	-shared					\
	-export-dynamic			\
	-avoid-version

Calendar_la_LIBADD =		\
	$(top_srcdir)/src/Libs/InputPlugin/libinputplugin.la

PluginManifestdir = $(pkgdatadir)/input/Calendar

PluginManifest_DATA = PluginManifest.xml

EXTRA_DIST = PluginManifest.xml

endif