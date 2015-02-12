/* ide-clang-translation-unit.c
 *
 * Copyright (C) 2015 Christian Hergert <christian@hergert.me>
 *
 * This file is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation; either version 3 of the
 * License, or (at your option) any later version.
 *
 * This file is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <clang-c/Index.h>
#include <glib/gi18n.h>

#include "ide-context.h"
#include "ide-clang-translation-unit.h"

typedef struct
{
  CXTranslationUnit  tu;
  gint64             sequence;
  IdeDiagnostics    *diagnostics;
} IdeClangTranslationUnitPrivate;

G_DEFINE_TYPE_WITH_PRIVATE (IdeClangTranslationUnit,
                            ide_clang_translation_unit,
                            IDE_TYPE_OBJECT)

enum {
  PROP_0,
  PROP_SEQUENCE,
  LAST_PROP
};

static GParamSpec *gParamSpecs [LAST_PROP];

IdeClangTranslationUnit *
_ide_clang_translation_unit_new (IdeContext        *context,
                                 CXTranslationUnit  tu,
                                 gint64             sequence)
{
  IdeClangTranslationUnitPrivate *priv;
  IdeClangTranslationUnit *ret;

  g_return_val_if_fail (IDE_IS_CONTEXT (context), NULL);
  g_return_val_if_fail (tu, NULL);

  ret = g_object_new (IDE_TYPE_CLANG_TRANSLATION_UNIT,
                      "context", context,
                      NULL);

  priv = ide_clang_translation_unit_get_instance_private (ret);

  priv->tu = tu;
  priv->sequence = sequence;

  return ret;
}

/**
 * ide_clang_translation_unit_get_diagnostics:
 *
 * Retrieves the diagnostics for the translation unit.
 *
 * Returns: (transfer none) (nullable): An #IdeDiagnostics or %NULL.
 */
IdeDiagnostics *
ide_clang_translation_unit_get_diagnostics (IdeClangTranslationUnit *self)
{
  IdeClangTranslationUnitPrivate *priv;

  g_return_val_if_fail (IDE_IS_CLANG_TRANSLATION_UNIT (self), NULL);

  priv = ide_clang_translation_unit_get_instance_private (self);

  if (!priv->diagnostics)
    {
    }

  return priv->diagnostics;
}

gint64
ide_clang_translation_unit_get_sequence (IdeClangTranslationUnit *self)
{
  IdeClangTranslationUnitPrivate *priv;

  g_return_val_if_fail (IDE_IS_CLANG_TRANSLATION_UNIT (self), -1);

  priv = ide_clang_translation_unit_get_instance_private (self);

  return priv->sequence;
}

static void
ide_clang_translation_unit_finalize (GObject *object)
{
  IdeClangTranslationUnit *self = (IdeClangTranslationUnit *)object;
  IdeClangTranslationUnitPrivate *priv = ide_clang_translation_unit_get_instance_private (self);

  clang_disposeTranslationUnit (priv->tu);

  G_OBJECT_CLASS (ide_clang_translation_unit_parent_class)->finalize (object);
}

static void
ide_clang_translation_unit_get_property (GObject    *object,
                                         guint       prop_id,
                                         GValue     *value,
                                         GParamSpec *pspec)
{
  IdeClangTranslationUnit *self = IDE_CLANG_TRANSLATION_UNIT (object);

  switch (prop_id)
    {
    case PROP_SEQUENCE:
      g_value_set_int64 (value, ide_clang_translation_unit_get_sequence (self));
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

static void
ide_clang_translation_unit_class_init (IdeClangTranslationUnitClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);

  object_class->finalize = ide_clang_translation_unit_finalize;
  object_class->get_property = ide_clang_translation_unit_get_property;

  gParamSpecs [PROP_SEQUENCE] =
    g_param_spec_int64 ("sequence",
                        _("Sequence"),
                        _("The sequence number when created."),
                        G_MININT64,
                        G_MAXINT64,
                        0,
                        (G_PARAM_READABLE | G_PARAM_STATIC_STRINGS));
  g_object_class_install_property (object_class, PROP_SEQUENCE,
                                   gParamSpecs [PROP_SEQUENCE]);
}

static void
ide_clang_translation_unit_init (IdeClangTranslationUnit *self)
{
}