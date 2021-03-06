/* ide-executer.h
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

#ifndef IDE_EXECUTER_H
#define IDE_EXECUTER_H

#include "ide-object.h"

G_BEGIN_DECLS

#define IDE_TYPE_EXECUTER               (ide_executer_get_type ())
#define IDE_EXECUTER(obj)               (G_TYPE_CHECK_INSTANCE_CAST ((obj), IDE_TYPE_EXECUTER, IdeExecuter))
#define IDE_IS_EXECUTER(obj)            (G_TYPE_CHECK_INSTANCE_TYPE ((obj), IDE_TYPE_EXECUTER))
#define IDE_EXECUTER_GET_INTERFACE(obj) (G_TYPE_INSTANCE_GET_INTERFACE ((obj), IDE_TYPE_EXECUTER, IdeExecuterInterface))

struct _IdeExecuterInterface
{
  GTypeInterface parent;
};

GType ide_executer_get_type (void);

G_END_DECLS

#endif /* IDE_EXECUTER_H */
