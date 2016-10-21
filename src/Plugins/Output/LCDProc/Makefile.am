## Process this file with automake to produce Makefile.in

if ENABLE_LCDPROC

outputpluginsdir = $(OUTPUT_PLUGINS_DIR)

outputplugins_LTLIBRARIES =		\
	LCDProc.la

LCDProc_la_SOURCES =			\
	LCDProcWidget.hpp			\
	LCDProcWidget.cpp			\
	LCDProcTextWidget.hpp		\
	LCDProcTextWidget.cpp		\
	LCDProcBarWidget.hpp		\
	LCDProcBarWidget.cpp		\
	LCDProcClockWidget.hpp		\
	LCDProcClockWidget.cpp		\
	LCDProcScreen.cpp			\
	LCDProcScreen.hpp			\
	LCDProc.hpp					\
	LCDProc.cpp

LCDProc_la_CXXFLAGS =				\
	-I$(top_srcdir)/src/Libs		\
	-I$(top_srcdir)/src/Libs/Types	\
	-I$(top_srcdir)/src/Libs/OutputPlugin

LCDProc_la_LDFLAGS =			\
	-module						\
	-shared						\
	-export-dynamic				\
	-avoid-version

LCDProc_la_LIBADD =											\
	$(top_srcdir)/src/Libs/OutputPlugin/liboutputplugin.la	\
	$(top_srcdir)/src/Libs/libsocks.la

endif