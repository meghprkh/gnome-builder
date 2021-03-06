/* gb-editor-workspace-private.h
 *
 * Copyright (C) 2014-2015 Christian Hergert <christian@hergert.me>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef GB_EDITOR_WORKSPACE_PRIVATE_H
#define GB_EDITOR_WORKSPACE_PRIVATE_H

#include <realtime-graphs.h>

#include "gb-project-tree.h"
#include "gb-view-grid.h"
#include "gb-workspace.h"

G_BEGIN_DECLS

struct _GbEditorWorkspace
{
  GbWorkspace    parent_instance;

  GSettings     *project_tree_settings;

  GtkPaned      *project_paned;
  GtkBox        *project_sidebar;
  GtkBox        *project_sidebar_header;
  GtkPopover    *project_popover;
  GtkMenuButton *project_button;
  GtkSpinner    *project_spinner;
  GbProjectTree *project_tree;
  GbViewGrid    *view_grid;
  GtkSeparator  *cpu_graph_sep;
  RgCpuGraph    *cpu_graph;

  guint          project_tree_position_timeout;
};

G_END_DECLS

#endif /* GB_EDITOR_WORKSPACE_PRIVATE_H */
