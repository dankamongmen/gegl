/* This file is part of GEGL.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with GEGL; if not, see <http://www.gnu.org/licenses/>.
 *
 * Copyright 2006, 2007 Øyvind Kolås <pippin@gimp.org>
 */

#ifndef __GEGL_TILE_BACKEND_H__
#define __GEGL_TILE_BACKEND_H__

#include "gegl-tile-source.h"

/***
 * GeglTileBackend is a simple basic GeglTileSource that provide and store tiles. This classe is
 * generic and is specialized in subclasses for different kind of storage.
 */

G_BEGIN_DECLS

#define GEGL_TYPE_TILE_BACKEND            (gegl_tile_backend_get_type ())
#define GEGL_TILE_BACKEND(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), GEGL_TYPE_TILE_BACKEND, GeglTileBackend))
#define GEGL_TILE_BACKEND_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  GEGL_TYPE_TILE_BACKEND, GeglTileBackendClass))
#define GEGL_IS_TILE_BACKEND(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GEGL_TYPE_TILE_BACKEND))
#define GEGL_IS_TILE_BACKEND_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  GEGL_TYPE_TILE_BACKEND))
#define GEGL_TILE_BACKEND_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  GEGL_TYPE_TILE_BACKEND, GeglTileBackendClass))

typedef struct _GeglTileBackendClass   GeglTileBackendClass;
typedef struct _GeglTileBackendPrivate GeglTileBackendPrivate;

struct _GeglTileBackend
{
  GeglTileSource          parent_instance;
  GeglTileBackendPrivate *priv;
};

struct _GeglTileBackendClass
{
  GeglTileSourceClass parent_class;
  gpointer            padding[4];
};

gint        gegl_tile_backend_get_tile_size (GeglTileBackend *tile_backend);
const Babl *gegl_tile_backend_get_format    (GeglTileBackend *tile_backend);

/* gets a pointer to the GeglTileStorage that uses the backend */
GeglTileSource *gegl_tile_backend_peek_storage  (GeglTileBackend *backend);

/* specify the extent of the backend, can be used to
 * pre-prime the backend with the width/height information when
 * constructing proxy GeglBuffers to interact with other systems
 */
void  gegl_tile_backend_set_extent    (GeglTileBackend *tile_backend,
                                       GeglRectangle   *rectangle);
GeglRectangle gegl_tile_backend_get_extent (GeglTileBackend *tile_backend);

GType gegl_tile_backend_get_type (void) G_GNUC_CONST;

/**
 * gegl_tile_backend_unlink_swap:
 * @path: the path where the gegl tile backend has swapped.
 *
 * Delete a swap file from disk. This must be used by tile backends which may
 * swap to disk under certain circonstances.
 *
 * For safety, this function will check that the swap file is in the swap
 * directory before deletion but it won't perform any other check.
 */
void gegl_tile_backend_unlink_swap (gchar *path);

G_END_DECLS

#endif
