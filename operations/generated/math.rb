#!/usr/bin/env ruby

copyright = '
/* !!!! AUTOGENERATED FILE generated by math.rb !!!!! 
 *
 *  Copyright 2006 Øyvind Kolås <pippin@gimp.org>
 *
 * !!!! AUTOGENERATED FILE !!!!!
 *
 */'

a = [
      ['add',          'c = c + value'],
      ['subtract',     'c = c - value'],
      ['multiply',     'c = c * value'],
      ['divide',       'c = value==0.0?0.0:c/value'],
      ['gamma',        'c = powf (c, value)'],
#     ['threshold',    'c = c>=value?1.0:0.0'],
#     ['invert',       'c = 1.0-c']
    ]
    
a.each do
    |item|

    name     = item[0] + ''
    filename = name + '.c'

    puts "generating #{filename}"
    file = File.open(filename, 'w')

    name        = item[0]
    capitalized = name.capitalize
    swapcased   = name.swapcase
    formula     = item[1]

    file.write copyright
    file.write "
#ifdef GEGL_CHANT_PROPERTIES
gegl_chant_double (value, -G_MAXDOUBLE, G_MAXDOUBLE, 0.0, \"global value used if aux doesn't contain data\")
#else

#define GEGL_CHANT_POINT_COMPOSER
#define GEGL_CHANT_NAME          #{name}
#define GEGL_CHANT_DESCRIPTION   \"Math operation #{name} (#{formula})\"
#define GEGL_CHANT_SELF          \"#{filename}\"
#define GEGL_CHANT_CATEGORIES    \"compositors:math\"
#define GEGL_CHANT_CONSTRUCT
#include \"gegl-chant.h\"

#include <math.h>

static void init (ChantInstance *self)
{
  GEGL_OPERATION_POINT_COMPOSER (self)->format = babl_format (\"RaGaBaA float\");
  GEGL_OPERATION_POINT_COMPOSER (self)->aux_format = babl_format (\"RGB float\");
}

static gboolean
evaluate (GeglOperation *op,
          void          *in_buf,
          void          *aux_buf,
          void          *out_buf,
          glong          n_pixels)
{
  gint i;
  gfloat *in = in_buf;
  gfloat *out = out_buf;
  gfloat *aux = aux_buf;

  if (aux == NULL)
      {
          gfloat value = GEGL_CHANT_INSTANCE (op)->value;
          for (i=0; i<n_pixels; i++)
            {
              int  j;
              gfloat c;
              for (j=0; j<3; j++)
                  {
                      c=in[j];
                      #{formula};
                      out[j]=c;
                  }
              out[3]=in[3];
              in += 4;
              out+= 4;
            }
      }
  else
      {
          for (i=0; i<n_pixels; i++)
            {
              int  j;
              gfloat c;
              gfloat value;
              for (j=0; j<3; j++)
                  {
                      c=in[j];
                      value=aux[j];
                      #{formula};
                      out[j]=c;
                  }
              out[3]=in[3];
              in += 4;
              aux += 3;
              out+= 4;
            }
      }
  
  return TRUE;
}
#endif
"
    file.close
end
