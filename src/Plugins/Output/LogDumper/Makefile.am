## Process this file with automake to produce Makefile.in

if ENABLE_LOGDUMPER

outputpluginsdir = $(OUTPUT_PLUGINS_DIR)

outputplugins_LTLIBRARIES =		\
	LogDumper.la

LogDumper_la_SOURCES =			\
	LogDumperWidget.hpp			\
	LogDumperWidget.cpp			\
	LogDumperScreen.hpp			\
	LogDumperScreen.cpp			\
	LogDumper.hpp				\
	LogDumper.cpp

LogDumper_la_CXXFLAGS =				\
	-I$(top_srcdir)/src/Libs		\
	-I$(top_srcdir)/src/Libs/Types	\
	-I$(top_srcdir)/src/Libs/OutputPlugin

LogDumper_la_LDFLAGS =			\
	-module						\
	-shared						\
	-export-dynamic				\
	-avoid-version

LogDumper_la_LIBADD =			\
	$(top_srcdir)/src/Libs/OutputPlugin/liboutputplugin.la

endif