/* gb-file-search-result.c
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

#include "gb-file-search-result.h"

struct _GbFileSearchResult
{
  IdeSearchResult parent_instance;
  gchar *path;
};

G_DEFINE_TYPE (GbFileSearchResult, gb_file_search_result, IDE_TYPE_SEARCH_RESULT)

enum {
  PROP_0,
  PROP_PATH,
  LAST_PROP
};

static GParamSpec *gParamSpecs [LAST_PROP];

static void
gb_file_search_result_finalize (GObject *object)
{
  GbFileSearchResult *self = (GbFileSearchResult *)object;

  g_free (self->path);

  G_OBJECT_CLASS (gb_file_search_result_parent_class)->finalize (object);
}

static void
gb_file_search_result_get_property (GObject    *object,
                                    guint       prop_id,
                                    GValue     *value,
                                    GParamSpec *pspec)
{
  GbFileSearchResult *self = (GbFileSearchResult *)object;

  switch (prop_id)
    {
    case PROP_PATH:
      g_value_set_string (value, self->path);
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

static void
gb_file_search_result_set_property (GObject      *object,
                                    guint         prop_id,
                                    const GValue *value,
                                    GParamSpec   *pspec)
{
  GbFileSearchResult *self = (GbFileSearchResult *)object;

  switch (prop_id)
    {
    case PROP_PATH:
      self->path = g_value_dup_string (value);
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

static void
gb_file_search_result_class_init (GbFileSearchResultClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);

  object_class->finalize = gb_file_search_result_finalize;
  object_class->get_property = gb_file_search_result_get_property;
  object_class->set_property = gb_file_search_result_set_property;

  gParamSpecs [PROP_PATH] =
    g_param_spec_string ("path",
                         "Path",
                         "The relative path to the file.",
                         NULL,
                         (G_PARAM_READWRITE | G_PARAM_CONSTRUCT_ONLY | G_PARAM_STATIC_STRINGS));

  g_object_class_install_properties (object_class, LAST_PROP, gParamSpecs);
}

static void
gb_file_search_result_init (GbFileSearchResult *self)
{
}
