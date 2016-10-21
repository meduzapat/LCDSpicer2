## Process this file with automake to produce Makefile.in

if ENABLE_KERNEL

inputpluginsdir = $(INPUT_PLUGINS_DIR)

inputplugins_LTLIBRARIES =	\
	Kernel.la

Kernel_la_SOURCES =			\
	Kernel.hpp				\
	Kernel.cpp

Kernel_la_CXXFLAGS =				\
	-I$(top_srcdir)/src/Libs		\
	-I$(top_srcdir)/src/Libs/Units	\
	-I$(top_srcdir)/src/Libs/Types	\
	-I$(top_srcdir)/src/Libs/InputPlugin

Kernel_la_LDFLAGS =			\
	-module					\
	-shared					\
	-export-dynamic			\
	-avoid-version

Kernel_la_LIBADD =				\
	$(top_srcdir)/src/Libs/Units/libunits.la	\
	$(top_srcdir)/src/Libs/InputPlugin/libinputplugin.la

PluginManifestdir = $(pkgdatadir)/input/Kernel

PluginManifest_DATA = PluginManifest.xml

EXTRA_DIST = PluginManifest.xml

endif