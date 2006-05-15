/* This file is part of GEGL
 *
 * GEGL is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * GEGL is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with GEGL; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 *
 * Copyright 2003 Calvin Williamson
 */

#ifndef __GEGL_CONNECTION_H__
#define __GEGL_CONNECTION_H__

G_BEGIN_DECLS


GeglConnection * gegl_connection_new             (GeglNode       *sink,
                                                  GeglPad        *sink_prop,
                                                  GeglNode       *source,
                                                  GeglPad        *source_prop);
GeglNode       * gegl_connection_get_source_node (GeglConnection *self);
GeglNode       * gegl_connection_get_sink_node   (GeglConnection *self);
GeglPad        * gegl_connection_get_source_prop (GeglConnection *self);
GeglPad        * gegl_connection_get_sink_prop   (GeglConnection *self);
void             gegl_connection_set_sink_node   (GeglConnection *self,
                                                  GeglNode       *sink);
void             gegl_connection_set_sink_prop   (GeglConnection *self,
                                                  GeglPad        *sink_prop);
void             gegl_connection_set_source_node (GeglConnection *self,
                                                  GeglNode       *source);
void             gegl_connection_set_source_prop (GeglConnection *self,
                                                  GeglPad        *source_prop);


G_END_DECLS

#endif /* __GEGL_CONNECTION_H__ */
