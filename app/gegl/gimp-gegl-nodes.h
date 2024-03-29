/* GIMP - The GNU Image Manipulation Program
 * Copyright (C) 1995 Spencer Kimball and Peter Mattis
 *
 * gimp-gegl-nodes.h
 * Copyright (C) 2012 Michael Natterer <mitch@gimp.org>
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

#ifndef __GIMP_GEGL_NODES_H__
#define __GIMP_GEGL_NODES_H__


GeglNode * gimp_gegl_create_flatten_node       (const GimpRGB        *background);
GeglNode * gimp_gegl_create_apply_opacity_node (GeglBuffer           *mask,
                                                gint                  mask_offset_x,
                                                gint                  mask_offset_y,
                                                gdouble               opacity);
GeglNode * gimp_gegl_create_apply_buffer_node  (GeglBuffer           *buffer,
                                                gint                  buffer_offset_x,
                                                gint                  buffer_offset_y,
                                                gint                  src_offset_x,
                                                gint                  src_offset_y,
                                                gint                  dest_offset_x,
                                                gint                  dest_offset_y,
                                                GeglBuffer           *mask,
                                                gint                  mask_offset_x,
                                                gint                  mask_offset_y,
                                                gdouble               opacity,
                                                GimpLayerModeEffects  mode,
                                                GimpComponentMask     affect);

GeglNode * gimp_gegl_add_buffer_source         (GeglNode             *parent,
                                                GeglBuffer           *buffer,
                                                gint                  offset_x,
                                                gint                  offset_y);

void       gimp_gegl_mode_node_set             (GeglNode             *node,
                                                GimpLayerModeEffects  mode,
                                                gdouble               opacity,
                                                gboolean              linear);
void       gimp_gegl_node_set_matrix           (GeglNode             *node,
                                                const GimpMatrix3    *matrix);


#endif /* __GIMP_GEGL_NODES_H__ */
