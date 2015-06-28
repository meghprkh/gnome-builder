/* ide-highlighter.c
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
#include <glib/gi18n.h>

#include "ide-context.h"
#include "ide-highlighter.h"

G_DEFINE_INTERFACE (IdeHighlighter, ide_highlighter, IDE_TYPE_OBJECT)

static void
dummy_update (IdeHighlighter       *self,
              IdeHighlightCallback  callback,
              const GtkTextIter    *range_begin,
              const GtkTextIter    *range_end,
              GtkTextIter          *location)
{
}

static void
dummy_set_engine (IdeHighlighter     *self,
                  IdeHighlightEngine *engine)
{
}

static void
ide_highlighter_default_init (IdeHighlighterInterface *iface)
{
  iface->set_engine = dummy_set_engine;
  iface->update = dummy_update;

  g_object_interface_install_property (iface,
                                       g_param_spec_object ("context",
                                                            "Context",
                                                            "Context",
                                                            IDE_TYPE_CONTEXT,
                                                            (G_PARAM_WRITABLE | G_PARAM_CONSTRUCT_ONLY | G_PARAM_STATIC_STRINGS)));
}

/**
 * ide_highlighter_update:
 * @self: A #IdeHighlighter.
 * @callback: (scope call): A callback to apply a given style.
 * @range_begin: The beginning of the range to update.
 * @range_end: The end of the range to update.
 * @location: (out): How far the highlighter got in the update.
 *
 * Incrementally processes more of the buffer for highlighting.  If @callback
 * returns %IDE_HIGHLIGHT_STOP, then this vfunc should stop processing and
 * return, having set @location to the current position of processing.
 *
 * If processing the entire range was successful, then @location should be set
 * to @range_end.
 */
void
ide_highlighter_update (IdeHighlighter       *self,
                        IdeHighlightCallback  callback,
                        const GtkTextIter    *range_begin,
                        const GtkTextIter    *range_end,
                        GtkTextIter          *location)
{
  g_return_if_fail (IDE_IS_HIGHLIGHTER (self));
  g_return_if_fail (callback != NULL);
  g_return_if_fail (range_begin);
  g_return_if_fail (range_end);

  IDE_HIGHLIGHTER_GET_IFACE (self)->update (self, callback, range_begin, range_end, location);
}
