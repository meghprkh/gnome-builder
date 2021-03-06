/* ide-project-file.c
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

#include "ide-project-file.h"

typedef struct
{
  GFile     *file;
  GFileInfo *file_info;
  gchar     *path;
} IdeProjectFilePrivate;

G_DEFINE_TYPE_WITH_PRIVATE (IdeProjectFile, ide_project_file, IDE_TYPE_PROJECT_ITEM)

enum {
  PROP_0,
  PROP_FILE,
  PROP_FILE_INFO,
  PROP_IS_DIRECTORY,
  PROP_NAME,
  PROP_PATH,
  LAST_PROP
};

static GParamSpec *gParamSpecs [LAST_PROP];

gboolean
ide_project_file_get_is_directory (IdeProjectFile *self)
{
  IdeProjectFilePrivate *priv = ide_project_file_get_instance_private (self);

  g_return_val_if_fail (IDE_IS_PROJECT_FILE (self), FALSE);

  if (priv->file_info)
    return (g_file_info_get_file_type (priv->file_info) == G_FILE_TYPE_DIRECTORY);

  return FALSE;
}

const gchar *
ide_project_file_get_path (IdeProjectFile *self)
{
  IdeProjectFilePrivate *priv = ide_project_file_get_instance_private (self);

  g_return_val_if_fail (IDE_IS_PROJECT_FILE (self), NULL);

  return priv->path;
}

static void
ide_project_file_set_path (IdeProjectFile *self,
                           const gchar    *path)
{
  IdeProjectFilePrivate *priv = ide_project_file_get_instance_private (self);

  g_return_if_fail (IDE_IS_PROJECT_FILE (self));

  if (priv->path != path)
    {
      g_free (priv->path);
      priv->path = g_strdup (path);
      g_object_notify_by_pspec (G_OBJECT (self), gParamSpecs [PROP_PATH]);
    }
}

const gchar *
ide_project_file_get_name (IdeProjectFile *self)
{
  IdeProjectFilePrivate *priv = ide_project_file_get_instance_private (self);
  const gchar *name;

  g_return_val_if_fail (IDE_IS_PROJECT_FILE (self), NULL);

  name = g_file_info_get_display_name (priv->file_info);
  if (name == NULL)
    name = g_file_info_get_name (priv->file_info);

  return name;
}

/**
 * ide_project_file_get_file:
 *
 * Retrieves the underlying #GFile represented by @file.
 *
 * Returns: (transfer none): Retrieves the #GFile represented by @file.
 */
GFile *
ide_project_file_get_file (IdeProjectFile *file)
{
  IdeProjectFilePrivate *priv = ide_project_file_get_instance_private (file);

  g_return_val_if_fail (IDE_IS_PROJECT_FILE (file), NULL);

  return priv->file;
}

void
ide_project_file_set_file (IdeProjectFile *self,
                           GFile          *file)
{
  IdeProjectFilePrivate *priv = ide_project_file_get_instance_private (self);

  g_return_if_fail (IDE_IS_PROJECT_FILE (self));
  g_return_if_fail (!file || G_IS_FILE (file));

  if (g_set_object (&priv->file, file))
    g_object_notify_by_pspec (G_OBJECT (self), gParamSpecs [PROP_FILE]);
}

/**
 * ide_project_file_get_file_info:
 *
 * Retrieves a #GFileInfo containing the basic information about @file. This
 * includes the name, display name, and file type.
 *
 * Returns: (transfer none): A #GFileInfo
 */
GFileInfo *
ide_project_file_get_file_info (IdeProjectFile *file)
{
  IdeProjectFilePrivate *priv = ide_project_file_get_instance_private (file);

  g_return_val_if_fail (IDE_IS_PROJECT_FILE (file), NULL);

  return priv->file_info;
}

void
ide_project_file_set_file_info (IdeProjectFile *file,
                                GFileInfo      *file_info)
{
  IdeProjectFilePrivate *priv = ide_project_file_get_instance_private (file);

  g_return_if_fail (IDE_IS_PROJECT_FILE (file));
  g_return_if_fail (!file_info || G_IS_FILE_INFO (file_info));

  if (g_set_object (&priv->file_info, file_info))
    {
      g_object_notify_by_pspec (G_OBJECT (file), gParamSpecs [PROP_FILE_INFO]);
      g_object_notify_by_pspec (G_OBJECT (file), gParamSpecs [PROP_NAME]);
    }
}

static void
ide_project_file_finalize (GObject *object)
{
  IdeProjectFile *self = (IdeProjectFile *)object;
  IdeProjectFilePrivate *priv = ide_project_file_get_instance_private (self);

  g_clear_pointer (&priv->path, g_free);
  g_clear_object (&priv->file);
  g_clear_object (&priv->file_info);

  G_OBJECT_CLASS (ide_project_file_parent_class)->finalize (object);
}

static void
ide_project_file_get_property (GObject    *object,
                               guint       prop_id,
                               GValue     *value,
                               GParamSpec *pspec)
{
  IdeProjectFile *self = IDE_PROJECT_FILE (object);

  switch (prop_id)
    {
    case PROP_FILE:
      g_value_set_object (value, ide_project_file_get_file (self));
      break;

    case PROP_FILE_INFO:
      g_value_set_object (value, ide_project_file_get_file_info (self));
      break;

    case PROP_IS_DIRECTORY:
      g_value_set_boolean (value, ide_project_file_get_is_directory (self));
      break;

    case PROP_NAME:
      g_value_set_string (value, ide_project_file_get_name (self));
      break;

    case PROP_PATH:
      g_value_set_string (value, ide_project_file_get_path (self));
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

static void
ide_project_file_set_property (GObject      *object,
                               guint         prop_id,
                               const GValue *value,
                               GParamSpec   *pspec)
{
  IdeProjectFile *self = IDE_PROJECT_FILE (object);

  switch (prop_id)
    {
    case PROP_FILE:
      ide_project_file_set_file (self, g_value_get_object (value));
      break;

    case PROP_FILE_INFO:
      ide_project_file_set_file_info (self, g_value_get_object (value));
      break;

    case PROP_PATH:
      ide_project_file_set_path (self, g_value_get_string (value));
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

static void
ide_project_file_class_init (IdeProjectFileClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);

  object_class->finalize = ide_project_file_finalize;
  object_class->get_property = ide_project_file_get_property;
  object_class->set_property = ide_project_file_set_property;

  gParamSpecs [PROP_FILE] =
    g_param_spec_object ("file",
                         _("File"),
                         _("A GFile to the underlying file."),
                         G_TYPE_FILE,
                         (G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS));

  gParamSpecs [PROP_FILE_INFO] =
    g_param_spec_object ("file-info",
                         _("File Info"),
                         _("The file information for the project file."),
                         G_TYPE_FILE_INFO,
                         (G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS));

  gParamSpecs [PROP_IS_DIRECTORY] =
    g_param_spec_boolean ("is-directory",
                          _("Is Directory"),
                          _("Is Directory"),
                          FALSE,
                          (G_PARAM_READABLE | G_PARAM_STATIC_STRINGS));

  gParamSpecs [PROP_NAME] =
    g_param_spec_string ("name",
                         _("Name"),
                         _("The short name of the file."),
                         NULL,
                         (G_PARAM_READABLE | G_PARAM_STATIC_STRINGS));

  gParamSpecs [PROP_PATH] =
    g_param_spec_string ("path",
                         _("Path"),
                         _("The path for the file within the project tree."),
                         NULL,
                         (G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS));

  g_object_class_install_properties (object_class, LAST_PROP, gParamSpecs);
}

static void
ide_project_file_init (IdeProjectFile *self)
{
}
