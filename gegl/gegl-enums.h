/* This file is part of GEGL
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
 * Copyright 2011 Michael Muré <batolettre@gmail.com>
 *
 */

/* This file hold public enum from GEGL. A proper registration for them is
 * generated automatically with glib-mkenums.
 *
 * TODO: currently, description are not supported by glib-mkenums, and therefore
 * an often ugly name is generated, and i18n is not supported.
 * gimp-mkenums support these description, with a custom system to allow i18n,
 * so it could be a way to achieve this.
 */

#ifndef __GEGL_ENUMS_H__
#define __GEGL_ENUMS_H__

G_BEGIN_DECLS

typedef enum {
  GEGL_SAMPLER_NEAREST = 0,   /*< desc="nearest"      >*/
  GEGL_SAMPLER_LINEAR,        /*< desc="linear"       >*/
  GEGL_SAMPLER_CUBIC,         /*< desc="cubic"        >*/
  GEGL_SAMPLER_NOHALO,        /*< desc="nohalo"       >*/
  GEGL_SAMPLER_LOHALO         /*< desc="lohalo"       >*/
} GeglSamplerType;
GType gegl_sampler_type_get_type   (void) G_GNUC_CONST;
#define GEGL_TYPE_SAMPLER_TYPE (gegl_sampler_type_get_type())

typedef enum {
  GEGL_ABYSS_NONE,
  GEGL_ABYSS_CLAMP,
  GEGL_ABYSS_LOOP,
  GEGL_ABYSS_BLACK,
  GEGL_ABYSS_WHITE
} GeglAbyssPolicy;
GType gegl_abyss_policy_get_type   (void) G_GNUC_CONST;
#define GEGL_ABYSS_POLICY_TYPE (gegl_abyss_policy_get_type())

G_END_DECLS

#endif /* __GEGL_ENUMS_H__ */
