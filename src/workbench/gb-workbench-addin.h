/* gb-workbench-addin.h
 *
 * Copyright (C) 2015 Christian Hergert <christian@hergert.me>
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

#ifndef GB_WORKBENCH_ADDIN_H
#define GB_WORKBENCH_ADDIN_H

#include <glib-object.h>

#include "gb-workbench.h"

G_BEGIN_DECLS

#define GB_TYPE_WORKBENCH_ADDIN (gb_workbench_addin_get_type ())

G_DECLARE_INTERFACE (GbWorkbenchAddin, gb_workbench_addin, GB, WORKBENCH_ADDIN, GObject)

struct _GbWorkbenchAddinInterface
{
  GTypeInterface parent;

  void (*load)   (GbWorkbenchAddin *self);
  void (*unload) (GbWorkbenchAddin *self);
};

void gb_workbench_addin_load   (GbWorkbenchAddin *self);
void gb_workbench_addin_unload (GbWorkbenchAddin *self);

G_END_DECLS

#endif /* GB_WORKBENCH_ADDIN_H */
