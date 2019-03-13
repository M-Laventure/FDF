#ifndef FDF_STRUCT_H
#define FDF_STRUCT_H
#define WHITE 255
#include "fdf.h"

typedef struct  s_env
{
                void *mlx_ptr;
                void *win_ptr;
                void *img_ptr;
                unsigned int *img_data;
                int bits_per_pixel;
                int size_line;
                int width;
                int height;
                int size_img;
                int endian;
}               t_env;

typedef struct s_pixel t_pixel;

typedef struct s_pixel
{
                unsigned int color;
                int z;
                int x;
                int y;
                struct s_pixel *next;
}              t_pixel;

typedef struct  s_map
{
                t_pixel *p_alpha;
                int nb_lines;
                int nb_col;
                int map_size;
}               t_map;

#endif
