
bin_PROGRAMS =				\
	lcdspicer2

lcdspicer2_SOURCES =		\
	XMLHelper.hpp			\
	XMLHelper.cpp			\
	PluginManifest.hpp		\
	InputPluginManifest.hpp	\
	InputPluginManifest.cpp	\
	PluginHandler.hpp		\
	PluginHandler.cpp		\
	OutputPluginHandler.hpp	\
	OutputPluginHandler.cpp	\
	InputPluginHandler.hpp	\
	InputPluginHandler.cpp	\
	Configuration.hpp		\
	Configuration.cpp		\
	Request.hpp				\
	Request.cpp				\
	DataLoader.hpp			\
	DataLoader.cpp			\
	Main.hpp				\
	Main.cpp

lcdspicer2_CPPFLAGS =						\
	-DPACKAGE_CONF_DIR=\"$(sysconfdir)\"	\
	-DPACKAGE_LOCALE_DIR=\"$(localedir)\"	\
	-DPACKAGE_SRC_DIR=\"$(srcdir)\"		\
	-DPACKAGE_DATA_DIR=\"$(pkgdatadir)\"	\
	-DPACKAGE_LIB_DIR=\"$(pkglibdir)\"

lcdspicer2_CXXFLAGS =		\
	-I../Libs				\
	-I../Libs/Types			\
	-I../Libs/InputPlugin	\
	-I../Libs/OutputPlugin	\
	$(LCDSPICER2_CFLAGS)	\
	-Wl,--no-as-needed

lcdspicer2_LDADD =											\
	$(LCDSPICER2_LIBS)										\
	$(top_srcdir)/src/Libs/liblogger.la						\
	$(top_srcdir)/src/Libs/libplugin.la						\
	$(top_srcdir)/src/Libs/Types/libvalue.la				\
	$(top_srcdir)/src/Libs/Types/libtypes.la				\
	$(top_srcdir)/src/Libs/InputPlugin/libinputplugin.la	\
	$(top_srcdir)/src/Libs/OutputPlugin/liboutputplugin.la
