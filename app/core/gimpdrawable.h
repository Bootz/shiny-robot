/* GIMP - The GNU Image Manipulation Program
 * Copyright (C) 1995 Spencer Kimball and Peter Mattis
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
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

#ifndef __GIMP_DRAWABLE_H__
#define __GIMP_DRAWABLE_H__


#include "gimpitem.h"


#define GIMP_TYPE_DRAWABLE            (gimp_drawable_get_type ())
#define GIMP_DRAWABLE(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), GIMP_TYPE_DRAWABLE, GimpDrawable))
#define GIMP_DRAWABLE_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), GIMP_TYPE_DRAWABLE, GimpDrawableClass))
#define GIMP_IS_DRAWABLE(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GIMP_TYPE_DRAWABLE))
#define GIMP_IS_DRAWABLE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GIMP_TYPE_DRAWABLE))
#define GIMP_DRAWABLE_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), GIMP_TYPE_DRAWABLE, GimpDrawableClass))


typedef struct _GimpDrawablePrivate GimpDrawablePrivate;
typedef struct _GimpDrawableClass   GimpDrawableClass;

struct _GimpDrawable
{
  GimpItem             parent_instance;

  GimpDrawablePrivate *private;
};

struct _GimpDrawableClass
{
  GimpItemClass  parent_class;

  /*  signals  */
  void          (* update)                (GimpDrawable         *drawable,
                                           gint                  x,
                                           gint                  y,
                                           gint                  width,
                                           gint                  height);
  void          (* alpha_changed)         (GimpDrawable         *drawable);

  /*  virtual functions  */
  gint64        (* estimate_memsize)      (const GimpDrawable   *drawable,
                                           gint                  width,
                                           gint                  height);
  void          (* invalidate_boundary)   (GimpDrawable         *drawable);
  void          (* get_active_components) (const GimpDrawable   *drawable,
                                           gboolean             *active);
  GimpComponentMask (* get_active_mask)   (const GimpDrawable   *drawable);
  void          (* convert_type)          (GimpDrawable         *drawable,
                                           GimpImage            *dest_image,
                                           const Babl           *new_format,
                                           GimpImageBaseType     new_base_type,
                                           GimpPrecision         new_precision,
                                           gint                  layer_dither_type,
                                           gint                  mask_dither_type,
                                           gboolean              push_undo);
  void          (* apply_buffer)          (GimpDrawable         *drawable,
                                           GeglBuffer           *buffer,
                                           const GeglRectangle  *buffer_region,
                                           gboolean              push_undo,
                                           const gchar          *undo_desc,
                                           gdouble               opacity,
                                           GimpLayerModeEffects  mode,
                                           GeglBuffer           *base_buffer,
                                           gint                  base_x,
                                           gint                  base_y);
  void          (* replace_buffer)        (GimpDrawable         *drawable,
                                           GeglBuffer           *buffer,
                                           const GeglRectangle  *buffer_region,
                                           gboolean              push_undo,
                                           const gchar          *undo_desc,
                                           gdouble               opacity,
                                           GeglBuffer           *mask,
                                           const GeglRectangle  *mask_region,
                                           gint                  x,
                                           gint                  y);
  GeglBuffer  * (* get_buffer)            (GimpDrawable         *drawable);
  void          (* set_buffer)            (GimpDrawable         *drawable,
                                           gboolean              push_undo,
                                           const gchar          *undo_desc,
                                           GeglBuffer           *buffer,
                                           gint                  offset_x,
                                           gint                  offset_y);
  void          (* push_undo)             (GimpDrawable         *drawable,
                                           const gchar          *undo_desc,
                                           GeglBuffer           *buffer,
                                           gint                  x,
                                           gint                  y,
                                           gint                  width,
                                           gint                  height);
  void          (* swap_pixels)           (GimpDrawable         *drawable,
                                           GeglBuffer           *buffer,
                                           gint                  x,
                                           gint                  y);
};


GType           gimp_drawable_get_type           (void) G_GNUC_CONST;

GimpDrawable  * gimp_drawable_new                (GType               type,
                                                  GimpImage          *image,
                                                  const gchar        *name,
                                                  gint                offset_x,
                                                  gint                offset_y,
                                                  gint                width,
                                                  gint                height,
                                                  const Babl         *format);

gint64          gimp_drawable_estimate_memsize   (const GimpDrawable *drawable,
                                                  gint                width,
                                                  gint                height);

void            gimp_drawable_update             (GimpDrawable       *drawable,
                                                  gint                x,
                                                  gint                y,
                                                  gint                width,
                                                  gint                height);
void            gimp_drawable_alpha_changed      (GimpDrawable       *drawable);

void           gimp_drawable_invalidate_boundary (GimpDrawable       *drawable);
void         gimp_drawable_get_active_components (const GimpDrawable *drawable,
                                                  gboolean           *active);
GimpComponentMask gimp_drawable_get_active_mask  (const GimpDrawable *drawable);

void            gimp_drawable_convert_type       (GimpDrawable       *drawable,
                                                  GimpImage          *dest_image,
                                                  GimpImageBaseType   new_base_type,
                                                  GimpPrecision       new_precision,
                                                  gint                layer_dither_type,
                                                  gint                mask_dither_type,
                                                  gboolean            push_undo);

void            gimp_drawable_apply_buffer       (GimpDrawable        *drawable,
                                                  GeglBuffer          *buffer,
                                                  const GeglRectangle *buffer_rect,
                                                  gboolean             push_undo,
                                                  const gchar         *undo_desc,
                                                  gdouble              opacity,
                                                  GimpLayerModeEffects mode,
                                                  GeglBuffer          *base_buffer,
                                                  gint                 base_x,
                                                  gint                 base_y);
void            gimp_drawable_replace_buffer     (GimpDrawable        *drawable,
                                                  GeglBuffer          *buffer,
                                                  const GeglRectangle *buffer_region,
                                                  gboolean             push_undo,
                                                  const gchar         *undo_desc,
                                                  gdouble              opacity,
                                                  GeglBuffer          *mask,
                                                  const GeglRectangle *mask_region,
                                                  gint                 x,
                                                  gint                 y);

GeglBuffer    * gimp_drawable_get_buffer         (GimpDrawable       *drawable);
void            gimp_drawable_set_buffer         (GimpDrawable       *drawable,
                                                  gboolean            push_undo,
                                                  const gchar        *undo_desc,
                                                  GeglBuffer         *buffer);
void            gimp_drawable_set_buffer_full    (GimpDrawable       *drawable,
                                                  gboolean            push_undo,
                                                  const gchar        *undo_desc,
                                                  GeglBuffer         *buffer,
                                                  gint                offset_x,
                                                  gint                offset_y);

GeglNode      * gimp_drawable_get_source_node    (GimpDrawable       *drawable);
GeglNode      * gimp_drawable_get_mode_node      (GimpDrawable       *drawable);

void            gimp_drawable_set_is_last_node   (GimpDrawable       *drawable,
                                                  gboolean            last_node);
gboolean        gimp_drawable_get_is_last_node   (GimpDrawable       *drawable);

void            gimp_drawable_swap_pixels        (GimpDrawable       *drawable,
                                                  GeglBuffer         *buffer,
                                                  gint                x,
                                                  gint                y);

void            gimp_drawable_push_undo          (GimpDrawable       *drawable,
                                                  const gchar        *undo_desc,
                                                  GeglBuffer         *buffer,
                                                  gint                x,
                                                  gint                y,
                                                  gint                width,
                                                  gint                height);

void            gimp_drawable_fill               (GimpDrawable       *drawable,
                                                  const GimpRGB      *color,
                                                  const GimpPattern  *pattern);
void            gimp_drawable_fill_by_type       (GimpDrawable       *drawable,
                                                  GimpContext        *context,
                                                  GimpFillType        fill_type);

const Babl    * gimp_drawable_get_format         (const GimpDrawable *drawable);
const Babl    * gimp_drawable_get_format_with_alpha
                                                 (const GimpDrawable *drawable);
const Babl    * gimp_drawable_get_format_without_alpha
                                                 (const GimpDrawable *drawable);
gboolean        gimp_drawable_has_alpha          (const GimpDrawable *drawable);
GimpImageBaseType gimp_drawable_get_base_type    (const GimpDrawable *drawable);
GimpPrecision   gimp_drawable_get_precision      (const GimpDrawable *drawable);
gboolean        gimp_drawable_is_rgb             (const GimpDrawable *drawable);
gboolean        gimp_drawable_is_gray            (const GimpDrawable *drawable);
gboolean        gimp_drawable_is_indexed         (const GimpDrawable *drawable);

const guchar  * gimp_drawable_get_colormap       (const GimpDrawable *drawable);

GimpLayer    * gimp_drawable_get_floating_sel    (const GimpDrawable *drawable);
void           gimp_drawable_attach_floating_sel (GimpDrawable       *drawable,
                                                  GimpLayer          *floating_sel);
void           gimp_drawable_detach_floating_sel (GimpDrawable       *drawable);


#endif /* __GIMP_DRAWABLE_H__ */
