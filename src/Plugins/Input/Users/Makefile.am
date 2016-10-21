## Process this file with automake to produce Makefile.in

if ENABLE_USERS

inputpluginsdir = $(libdir)/$(PACKAGE_TARNAME)/plugins/input

inputplugins_LTLIBRARIES =	\
	Users.la

Users_la_SOURCES =			\
	Users.hpp				\
	Users.cpp

Users_la_CXXFLAGS =						\
	-I$(top_srcdir)/src/Libs			\
	-I$(top_srcdir)/src/Libs/Types		\
	-I$(top_srcdir)/src/Libs/InputPlugin

Users_la_LDFLAGS =			\
	-module					\
	-shared					\
	-export-dynamic			\
	-avoid-version

Users_la_LIBADD =			\
	$(top_srcdir)/src/Libs/InputPlugin/libinputplugin.la

PluginManifestdir = $(pkgdatadir)/input/Users

PluginManifest_DATA = PluginManifest.xml

EXTRA_DIST = PluginManifest.xml

endif