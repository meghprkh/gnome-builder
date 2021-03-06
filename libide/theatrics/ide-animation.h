/* ide-animation.h
 *
 * Copyright (C) 2013 Christian Hergert <christian@hergert.me>
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

#ifndef IDE_ANIMATION_H
#define IDE_ANIMATION_H

#include <gdk/gdk.h>

G_BEGIN_DECLS

#define IDE_TYPE_ANIMATION      (ide_animation_get_type())
#define IDE_TYPE_ANIMATION_MODE (ide_animation_mode_get_type())

G_DECLARE_FINAL_TYPE (IdeAnimation, ide_animation,
                      IDE, ANIMATION, GInitiallyUnowned)

typedef enum   _IdeAnimationMode    IdeAnimationMode;

enum _IdeAnimationMode
{
  IDE_ANIMATION_LINEAR,
  IDE_ANIMATION_EASE_IN_QUAD,
  IDE_ANIMATION_EASE_OUT_QUAD,
  IDE_ANIMATION_EASE_IN_OUT_QUAD,
  IDE_ANIMATION_EASE_IN_CUBIC,
  IDE_ANIMATION_EASE_OUT_CUBIC,

  IDE_ANIMATION_LAST
};

GType         ide_animation_mode_get_type (void);
void          ide_animation_start         (IdeAnimation      *animation);
void          ide_animation_stop          (IdeAnimation      *animation);
void          ide_animation_add_property  (IdeAnimation      *animation,
                                           GParamSpec       *pspec,
                                           const GValue     *value);
IdeAnimation* ide_object_animate          (gpointer          object,
                                           IdeAnimationMode   mode,
                                           guint             duration_msec,
                                           GdkFrameClock    *frame_clock,
                                           const gchar      *first_property,
                                           ...) G_GNUC_NULL_TERMINATED;
IdeAnimation* ide_object_animate_full     (gpointer          object,
                                           IdeAnimationMode   mode,
                                           guint             duration_msec,
                                           GdkFrameClock    *frame_clock,
                                           GDestroyNotify    notify,
                                           gpointer          notify_data,
                                           const gchar      *first_property,
                                           ...) G_GNUC_NULL_TERMINATED;

G_END_DECLS

#endif /* IDE_ANIMATION_H */
