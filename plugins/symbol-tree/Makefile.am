DISTCLEANFILES =
BUILT_SOURCES =
CLEANFILES =
EXTRA_DIST =

noinst_LTLIBRARIES = libsymbol-tree.la

libsymbol_tree_la_SOURCES = \
	symbol-tree-resources.c \
	symbol-tree-resources.h \
	symbol-tree.c \
	symbol-tree.h \
	$(NULL)

# XXX: temporary, since we need to extract lots of src/ into plugins
libsymbol_tree_la_CFLAGS = \
	$(BUILDER_CFLAGS) \
	-I$(top_srcdir)/src \
	-I$(top_srcdir)/src/documents \
	-I$(top_srcdir)/src/views \
	-I$(top_srcdir)/src/tree \
	-I$(top_srcdir)/src/workbench \
	-I$(top_srcdir)/src/workspace \
	-I$(top_srcdir)/libide \
	$(NULL)

libsymbol_tree_la_LIBADD = \
	$(BUILDER_LIBS) \
	$(top_builddir)/libide/libide-1.0.la \
	$(NULL)

libsymbol_tree_la_LDFLAGS = \
	-avoid-version \
	-module \
	$(NULL)

glib_resources_c = symbol-tree-resources.c
glib_resources_h = symbol-tree-resources.h
glib_resources_xml = symbol-tree.gresource.xml
glib_resources_namespace = symbol_tree
include $(top_srcdir)/build/autotools/Makefile.am.gresources


-include $(top_srcdir)/git.mk