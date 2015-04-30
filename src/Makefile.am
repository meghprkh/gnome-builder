CLEANFILES =
DISTCLEANFILES =
BUILT_SOURCES =
EXTRA_DIST =

bin_PROGRAMS = gnome-builder

noinst_LTLIBRARIES = libgnome-builder.la

libgnome_builder_la_SOURCES = \
	$(gnome_builder_built_sources) \
	app/gb-application-actions.c \
	app/gb-application-actions.h \
	app/gb-application-credits.h \
	app/gb-application-private.h \
	app/gb-application.c \
	app/gb-application.h \
	commands/gb-command-bar-item.c \
	commands/gb-command-bar-item.h \
	commands/gb-command-bar.c \
	commands/gb-command-bar.h \
	commands/gb-command-gaction-provider.c \
	commands/gb-command-gaction-provider.h \
	commands/gb-command-gaction.c \
	commands/gb-command-gaction.h \
	commands/gb-command-manager.c \
	commands/gb-command-manager.h \
	commands/gb-command-provider.c \
	commands/gb-command-provider.h \
	commands/gb-command-result.c \
	commands/gb-command-result.h \
	commands/gb-command-vim-provider.c \
	commands/gb-command-vim-provider.h \
	commands/gb-command-vim.c \
	commands/gb-command-vim.h \
	commands/gb-command.c \
	commands/gb-command.h \
	devhelp/gb-devhelp-document.c \
	devhelp/gb-devhelp-document.h \
	devhelp/gb-devhelp-view.c \
	devhelp/gb-devhelp-view.h \
	dialogs/gb-new-project-dialog.c \
	dialogs/gb-new-project-dialog.h \
	dialogs/gb-projects-dialog.c \
	dialogs/gb-projects-dialog.h \
	dialogs/gb-recent-project-row.c \
	dialogs/gb-recent-project-row.h \
	documents/gb-document.c \
	documents/gb-document.h \
	editor/gb-editor-document.c \
	editor/gb-editor-document.h \
	editor/gb-editor-frame-actions.c \
	editor/gb-editor-frame-actions.h \
	editor/gb-editor-frame-private.h \
	editor/gb-editor-frame.c \
	editor/gb-editor-frame.h \
	editor/gb-editor-map-bin.c \
	editor/gb-editor-map-bin.h \
	editor/gb-editor-settings-widget.c \
	editor/gb-editor-settings-widget.h \
	editor/gb-editor-tweak-widget.c \
	editor/gb-editor-tweak-widget.h \
	editor/gb-editor-view-actions.c \
	editor/gb-editor-view-actions.h \
	editor/gb-editor-view-private.h \
	editor/gb-editor-view.c \
	editor/gb-editor-view.h \
	editor/gb-editor-workspace-actions.c \
	editor/gb-editor-workspace-actions.h \
	editor/gb-editor-workspace-private.h \
	editor/gb-editor-workspace.c \
	editor/gb-editor-workspace.h \
	gd/gd-tagged-entry.c \
	gd/gd-tagged-entry.h \
	gedit/gedit-close-button.c \
	gedit/gedit-close-button.h \
	gedit/gedit-menu-stack-switcher.c \
	gedit/gedit-menu-stack-switcher.h \
	html/gb-html-document.c \
	html/gb-html-document.h \
	html/gb-html-view.c \
	html/gb-html-view.h \
	keybindings/gb-keybindings.c \
	keybindings/gb-keybindings.h \
	nautilus/nautilus-floating-bar.c \
	nautilus/nautilus-floating-bar.h \
	preferences/gb-preferences-page-editor.c \
	preferences/gb-preferences-page-editor.h \
	preferences/gb-preferences-page-experimental.c \
	preferences/gb-preferences-page-experimental.h \
	preferences/gb-preferences-page-git.c \
	preferences/gb-preferences-page-git.h \
	preferences/gb-preferences-page-keybindings.c \
	preferences/gb-preferences-page-keybindings.h \
	preferences/gb-preferences-page-language.c \
	preferences/gb-preferences-page-language.h \
	preferences/gb-preferences-page.c \
	preferences/gb-preferences-page.h \
	preferences/gb-preferences-switch.c \
	preferences/gb-preferences-switch.h \
	preferences/gb-preferences-window.c \
	preferences/gb-preferences-window.h \
	project-tree/gb-new-file-popover.c \
	project-tree/gb-new-file-popover.h \
	project-tree/gb-project-tree-actions.c \
	project-tree/gb-project-tree-actions.h \
	project-tree/gb-project-tree-builder.c \
	project-tree/gb-project-tree-builder.h \
	project-tree/gb-project-tree-private.h \
	project-tree/gb-project-tree.c \
	project-tree/gb-project-tree.h \
	project-tree/gb-rename-file-popover.c \
	project-tree/gb-rename-file-popover.h \
	scrolledwindow/gb-scrolled-window.c \
	scrolledwindow/gb-scrolled-window.h \
	search/gb-search-box.c \
	search/gb-search-box.h \
	search/gb-search-display-group.c \
	search/gb-search-display-group.h \
	search/gb-search-display-row.c \
	search/gb-search-display-row.h \
	search/gb-search-display.c \
	search/gb-search-display.h \
	support/gb-support.c \
	support/gb-support.h \
	tree/gb-tree-builder.c \
	tree/gb-tree-builder.h \
	tree/gb-tree-node.c \
	tree/gb-tree-node.h \
	tree/gb-tree.c \
	tree/gb-tree.h \
	util/gb-cairo.c \
	util/gb-cairo.h \
	util/gb-dnd.c \
	util/gb-dnd.h \
	util/gb-file-manager.c \
	util/gb-file-manager.h \
	util/gb-gdk.c \
	util/gb-gdk.h \
	util/gb-glib.c \
	util/gb-glib.h \
	util/gb-gtk.c \
	util/gb-gtk.h \
	util/gb-pango.c \
	util/gb-pango.h \
	util/gb-rgba.c \
	util/gb-rgba.h \
	util/gb-string.c \
	util/gb-string.h \
	util/gb-widget.c \
	util/gb-widget.h \
	views/gb-view-grid.c \
	views/gb-view-grid.h \
	views/gb-view-stack-actions.c \
	views/gb-view-stack-actions.h \
	views/gb-view-stack-private.h \
	views/gb-view-stack.c \
	views/gb-view-stack.h \
	views/gb-view.c \
	views/gb-view.h \
	vim/gb-vim.c \
	vim/gb-vim.h \
	workbench/gb-workbench-actions.c \
	workbench/gb-workbench-actions.h \
	workbench/gb-workbench-private.h \
	workbench/gb-workbench-types.h \
	workbench/gb-workbench.c \
	workbench/gb-workbench.h \
	workbench/gb-workspace.c \
	workbench/gb-workspace.h \
        css/gb-css-provider.c \
        css/gb-css-provider.h \
        util/gb-settings.c \
        util/gb-settings.h \
	$(NULL)

nodist_libgnome_builder_la_SOURCES = \
	resources/gb-resources.c \
	resources/gb-resources.h \
	$(NULL)

libgnome_builder_la_LIBADD = \
	$(BUILDER_LIBS) \
	$(OPTIMIZE_LDFLAGS) \
	$(top_builddir)/libide/libide-1.0.la \
	-lm

libgnome_builder_la_CFLAGS = \
	-DPACKAGE_DATADIR="\"${datadir}\"" \
	-DPACKAGE_LOCALE_DIR=\""${datadir}/locale"\" \
	$(BUILDER_CFLAGS) \
	$(DEBUG_CFLAGS) \
	$(OPTIMIZE_CFLAGS) \
	-I$(builddir)/resources \
	-I$(builddir)/util \
	-I$(srcdir)/app \
	-I$(srcdir)/commands \
	-I$(srcdir)/css \
	-I$(srcdir)/devhelp \
	-I$(srcdir)/dialogs \
	-I$(srcdir)/documents \
	-I$(srcdir)/editor \
	-I$(srcdir)/gd \
	-I$(srcdir)/gedit \
	-I$(srcdir)/html \
	-I$(srcdir)/keybindings \
	-I$(srcdir)/nautilus \
	-I$(srcdir)/preferences \
	-I$(srcdir)/project-tree \
	-I$(srcdir)/resources \
	-I$(srcdir)/scrolledwindow \
	-I$(srcdir)/search \
	-I$(srcdir)/support \
	-I$(srcdir)/tree \
	-I$(srcdir)/util \
	-I$(srcdir)/views \
	-I$(srcdir)/vim \
	-I$(srcdir)/workbench \
	-I$(top_builddir)/libide \
	-I$(top_srcdir)/libide \
	$(NULL)

gnome_builder_SOURCES = main.c
gnome_builder_CFLAGS = $(libgnome_builder_la_CFLAGS)
gnome_builder_LDADD = \
	$(top_builddir)/libide/libide-1.0.la \
	libgnome-builder.la \
	$(NULL)

glib_resources_c = resources/gb-resources.c
glib_resources_h = resources/gb-resources.h
glib_resources_xml = resources/gnome-builder.gresource.xml
glib_resources_namespace = gb
include $(top_srcdir)/build/autotools/Makefile.am.gresources

-include $(top_srcdir)/git.mk