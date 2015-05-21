/* ide-ctags-highlighter.c
 *
 * Copyright (C) 2015 Dimitris Zenios <dimitris.zenios@gmail.com>
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

#include "ide-ctags-highlighter.h"
#include "ide-debug.h"

struct _IdeCtagsHighlighter
{
  IdeHighlighter parent_instance;
  GPtrArray     *indexes;
};

G_DEFINE_TYPE (IdeCtagsHighlighter, ide_ctags_highlighter, IDE_TYPE_HIGHLIGHTER)

static inline gboolean
accepts_char (gunichar ch)
{
  return (ch == '_' || g_unichar_isalnum (ch));
}

static gboolean
select_next_word (GtkTextIter *begin,
                  GtkTextIter *end)
{
  g_assert (begin);
  g_assert (end);

  *end = *begin;

  while (!accepts_char (gtk_text_iter_get_char (begin)))
    if (!gtk_text_iter_forward_char (begin))
      return FALSE;

  *end = *begin;

  while (accepts_char (gtk_text_iter_get_char (end)))
    if (!gtk_text_iter_forward_char (end))
      return !gtk_text_iter_equal (begin, end);

  return TRUE;
}

static const gchar *
get_tag_from_kind (IdeCtagsIndexEntryKind kind)
{
  switch (kind)
    {
    case IDE_CTAGS_INDEX_ENTRY_FUNCTION:
      return IDE_CTAGS_HIGHLIGHTER_FUNCTION_NAME;

    case IDE_CTAGS_INDEX_ENTRY_ENUMERATOR:
    case IDE_CTAGS_INDEX_ENTRY_ENUMERATION_NAME:
      return IDE_CTAGS_HIGHLIGHTER_ENUM_NAME;

    case IDE_CTAGS_INDEX_ENTRY_TYPEDEF:
    case IDE_CTAGS_INDEX_ENTRY_STRUCTURE:
      return IDE_CTAGS_HIGHLIGHTER_TYPE;

    case IDE_CTAGS_INDEX_ENTRY_ANCHOR:
    case IDE_CTAGS_INDEX_ENTRY_CLASS_NAME:
    case IDE_CTAGS_INDEX_ENTRY_DEFINE:
    case IDE_CTAGS_INDEX_ENTRY_FILE_NAME:
    case IDE_CTAGS_INDEX_ENTRY_MEMBER:
    case IDE_CTAGS_INDEX_ENTRY_PROTOTYPE:
    case IDE_CTAGS_INDEX_ENTRY_UNION:
    case IDE_CTAGS_INDEX_ENTRY_VARIABLE:

    default:
      return NULL;
    }
}

static const gchar *get_tag (IdeCtagsHighlighter *self,const gchar *word)
{
  const IdeCtagsIndexEntry *entries;
  gsize n_entries;
  gsize i;

  for (i = 0; i < self->indexes->len; i++)
    {
      IdeCtagsIndex *item = g_ptr_array_index (self->indexes, i);
      entries = ide_ctags_index_lookup_prefix (item, word, &n_entries);
      if ((entries == NULL) || (n_entries == 0))
        continue;

      return get_tag_from_kind (entries[0].kind);
    }
  return NULL;
}

static void
ide_ctags_highlighter_real_update (IdeHighlighter       *highlighter,
                                   IdeHighlightCallback  callback,
                                   const GtkTextIter    *range_begin,
                                   const GtkTextIter    *range_end,
                                   GtkTextIter          *location)
{
  GtkTextBuffer *text_buffer;
  GtkSourceBuffer *source_buffer;
  IdeBuffer *buffer;
  GtkTextIter begin;
  GtkTextIter end;

  g_assert (IDE_IS_CTAGS_HIGHLIGHTER (highlighter));
  g_assert (callback != NULL);
  g_assert (range_begin != NULL);
  g_assert (range_end != NULL);
  g_assert (location != NULL);

  if (!(text_buffer = gtk_text_iter_get_buffer (range_begin)) ||
      !IDE_IS_BUFFER (text_buffer) ||
      !(source_buffer = GTK_SOURCE_BUFFER (text_buffer)) ||
      !(buffer = IDE_BUFFER (text_buffer)))
    return;

  begin = end = *location = *range_begin;

  while (gtk_text_iter_compare (&begin, range_end) < 0)
    {
      if (!select_next_word (&begin, &end))
        goto completed;

      if (gtk_text_iter_compare (&begin, range_end) >= 0)
        goto completed;

      g_assert (!gtk_text_iter_equal (&begin, &end));

      if (!gtk_source_buffer_iter_has_context_class (source_buffer, &begin, "string") &&
          !gtk_source_buffer_iter_has_context_class (source_buffer, &begin, "path") &&
          !gtk_source_buffer_iter_has_context_class (source_buffer, &begin, "comment"))
        {
          const gchar *tag;
          gchar *word;

          word = gtk_text_iter_get_slice (&begin, &end);
          tag = get_tag (IDE_CTAGS_HIGHLIGHTER (highlighter), word);
          g_free (word);

          if (tag != NULL)
            {
              if (callback (&begin, &end, tag) == IDE_HIGHLIGHT_STOP)
                {
                  *location = end;
                  return;
                }
            }
        }

      begin = end;
    }

completed:
  *location = *range_end;
}

void
ide_ctags_highlighter_add_index (IdeCtagsHighlighter *self,
                                 IdeCtagsIndex       *index)
{
  GFile *file;
  gsize i;

  IDE_ENTRY;

  g_return_if_fail (IDE_IS_CTAGS_HIGHLIGHTER (self));
  g_return_if_fail (!index || IDE_IS_CTAGS_INDEX (index));
  g_return_if_fail (self->indexes != NULL);

  file = ide_ctags_index_get_file (index);

  for (i = 0; i < self->indexes->len; i++)
    {
      IdeCtagsIndex *item = g_ptr_array_index (self->indexes, i);
      GFile *item_file = ide_ctags_index_get_file (item);

      if (g_file_equal (item_file, file))
        {
          g_ptr_array_remove_index_fast (self->indexes, i);
          g_ptr_array_add (self->indexes, g_object_ref (index));

          IDE_EXIT;
        }
    }

  g_ptr_array_add (self->indexes, g_object_ref (index));

  IDE_EXIT;
}

static void
ide_ctags_highlighter_finalize (GObject *object)
{
  IdeCtagsHighlighter *self = (IdeCtagsHighlighter *)object;

  g_clear_pointer (&self->indexes, g_ptr_array_unref);

  G_OBJECT_CLASS (ide_ctags_highlighter_parent_class)->finalize (object);
}

static void
ide_ctags_highlighter_class_init (IdeCtagsHighlighterClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  IdeHighlighterClass *highlighter_class = IDE_HIGHLIGHTER_CLASS (klass);

  object_class->finalize = ide_ctags_highlighter_finalize;
  highlighter_class->update = ide_ctags_highlighter_real_update;

}

static void
ide_ctags_highlighter_init (IdeCtagsHighlighter *self)
{
  self->indexes = g_ptr_array_new_with_free_func (g_object_unref);
}