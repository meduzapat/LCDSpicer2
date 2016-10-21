## Process this file with automake to produce Makefile.in

if HAVE_DOCUMENTATION

doxyfile.stamp:
	$(DOXYGEN) $(top_srcdir)/doc/lcdspicer2.doxyfile
	echo Timestamp > doxyfile.stamp

CLEANFILES = doxyfile.stamp

all-local: doxyfile.stamp

clean-local:
	rm -rf $(top_srcdir)/doc/html

install-data-local:
	cp -Rfu $(top_srcdir)/doc/html $(htmldir)/html

uninstall-local:
	rm -rf $(htmldir)/html

endif