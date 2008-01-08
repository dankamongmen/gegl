/* This file is an image processing operation for GEGL
 *
 * GEGL is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * GEGL is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with GEGL; if not, see <http://www.gnu.org/licenses/>.
 *
 * Copyright 2006 Øyvind Kolås <pippin@gimp.org>
 */
#if GEGL_CHANT_PROPERTIES

gegl_chant_double (radius, 0.0, 200.0, 4.0,
  "Radius of square pixel region, (width and height will be radius*2+1.")

#else

#define GEGL_CHANT_NAME            box_max
#define GEGL_CHANT_SELF            "box-max.c"
#define GEGL_CHANT_DESCRIPTION     "Sets the target pixel to the value of the maximum value in a box surrounding the pixel."
#define GEGL_CHANT_CATEGORIES      "misc"

#define GEGL_CHANT_AREA_FILTER
#define GEGL_CHANT_PREPARE

#include "gegl-chant.h"

static void hor_max (GeglBuffer *src,
                     GeglBuffer *dst,
                     gint        radius);

static void ver_max (GeglBuffer *src,
                     GeglBuffer *dst,
                     gint        radius);

#include <stdio.h>

static void prepare (GeglOperation *operation)
{
  gegl_operation_set_format (operation, "output", babl_format ("RGBA float"));
}

static gboolean
process (GeglOperation       *operation,
         GeglNodeContext     *context,
         GeglBuffer          *input,
         GeglBuffer          *output,
         const GeglRectangle *result)
{
  GeglOperationFilter *filter;
  GeglChantOperation  *self;

  filter = GEGL_OPERATION_FILTER (operation);
  self   = GEGL_CHANT_OPERATION (operation);

    {
      GeglBuffer   *temp_in;
      GeglBuffer   *temp;
      GeglRectangle compute = gegl_operation_compute_input_request (operation, "input", result);

      temp_in = gegl_buffer_create_sub_buffer (input, &compute);
      temp   = gegl_buffer_new (&compute, babl_format ("RGBA float"));

      hor_max (temp_in, temp, self->radius);
      ver_max (temp, output, self->radius);
      g_object_unref (temp);
      g_object_unref (temp_in);

      {
        GeglBuffer *cropped = gegl_buffer_create_sub_buffer (output, result);

        gegl_node_context_set_object (context, "output", G_OBJECT (cropped));
      }
    }

  return  TRUE;
}

static inline gfloat
get_max_component (gfloat *buf,
                   gint    buf_width,
                   gint    buf_height,
                   gint    x0,
                   gint    y0,
                   gint    width,
                   gint    height,
                   gint    component)
{
  gint    x, y;
  gfloat max=-1000000000.0;
  gint    count=0;

  gint offset = (y0 * buf_width + x0) * 4 + component;

  for (y=y0; y<y0+height; y++)
    {
    for (x=x0; x<x0+width; x++)
      {
        if (x>=0 && x<buf_width &&
            y>=0 && y<buf_height)
          {
            if (buf [offset] > max)
              max = buf[offset];
            count++;
          }
        offset+=4;
      }
      offset+= (buf_width * 4) - 4 * width;
    }
   return max;
}

static void
hor_max (GeglBuffer *src,
         GeglBuffer *dst,
         gint        radius)
{
  gint u,v;
  gint offset;
  gfloat *src_buf;
  gfloat *dst_buf;

  src_buf = g_malloc0 (gegl_buffer_get_pixel_count (src) * 4 * 4);
  dst_buf = g_malloc0 (gegl_buffer_get_pixel_count (dst) * 4 * 4);

  gegl_buffer_get (src, 1.0, NULL, babl_format ("RGBA float"), src_buf, GEGL_AUTO_ROWSTRIDE);

  offset = 0;
  for (v=0; v<gegl_buffer_get_height (dst); v++)
    for (u=0; u<gegl_buffer_get_width (dst); u++)
      {
        gint i;

        for (i=0; i<4; i++)
          dst_buf [offset++] = get_max_component (src_buf,
                               gegl_buffer_get_width (src),
                               gegl_buffer_get_height (src),
                               u - radius,
                               v,
                               1 + radius*2,
                               1,
                               i);
      }

  gegl_buffer_set (dst, NULL, babl_format ("RGBA float"), dst_buf, GEGL_AUTO_ROWSTRIDE);
  g_free (src_buf);
  g_free (dst_buf);
}


static void
ver_max (GeglBuffer *src,
         GeglBuffer *dst,
         gint        radius)
{
  gint u,v;
  gint offset;
  gfloat *src_buf;
  gfloat *dst_buf;

  src_buf = g_malloc0 (gegl_buffer_get_pixel_count (src) * 4 * 4);
  dst_buf = g_malloc0 (gegl_buffer_get_pixel_count (dst) * 4 * 4);

  gegl_buffer_get (src, 1.0, NULL, babl_format ("RGBA float"), src_buf, GEGL_AUTO_ROWSTRIDE);

  offset=0;
  for (v=0; v<gegl_buffer_get_height (dst); v++)
    for (u=0; u<gegl_buffer_get_width (dst); u++)
      {
        gint c;

        for (c=0; c<4; c++)
          dst_buf [offset++] =
           get_max_component (src_buf,
                              gegl_buffer_get_width (src),
                              gegl_buffer_get_height (src),
                              u,
                              v - radius,
                              1,
                              1 + radius * 2,
                              c);
      }

  gegl_buffer_set (dst, NULL, babl_format ("RGBA float"), dst_buf, GEGL_AUTO_ROWSTRIDE);
  g_free (src_buf);
  g_free (dst_buf);
}

#include <math.h>
static void tickle (GeglOperation *operation)
{
  GeglOperationAreaFilter *area = GEGL_OPERATION_AREA_FILTER (operation);
  GeglChantOperation      *filter = GEGL_CHANT_OPERATION (operation);
  area->left = area->right = area->top = area->bottom =
      ceil (filter->radius);
}

#endif
