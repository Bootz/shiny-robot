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

#ifndef __GIMP_DRAWABLE_PRIVATE_H__
#define __GIMP_DRAWABLE_PRIVATE_H__

struct _GimpDrawablePrivate
{
  GeglBuffer    *buffer; /* buffer for drawable data */
  GeglBuffer    *shadow; /* shadow buffer            */

  GeglNode      *source_node;
  GeglNode      *buffer_source_node;

  GimpLayer     *floating_selection;
  GeglNode      *fs_crop_node;
  GeglNode      *fs_offset_node;
  GeglNode      *fs_mode_node;

  GeglNode      *mode_node;

  gboolean       is_last_node;
};

#endif /* __GIMP_DRAWABLE_PRIVATE_H__ */
