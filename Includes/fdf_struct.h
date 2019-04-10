#ifndef FDF_STRUCT_H
# define FDF_STRUCT_H
# define PROJ(x) x == 1 ? (1) : (0)
# define CTE1 0.5
# define CTE2 0.5 
# include "fdf.h"

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

typedef struct  s_env
{
                void *mlx_ptr;
                void *win_ptr;
                void *img_ptr;
                int *img_data;
                int bits_per_pixel;
                int stop;
                int gap;
                int size_line;
                int width;
                int height;
                int size_img;
                int endian;
				int x_gap;
				int y_gap;
				int x_start;
				int y_start;
				int proj_type;
				int x1;
				int y1;
				int z1;
				int z2;
				int x2;
				int y2;
                t_map *map;
}               t_env;

#endif
