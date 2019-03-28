#ifndef FDF_STRUCT_H
# define FDF_STRUCT_H
# define CTE1(z) z != 0 ? (0.5) : (0)
# define CTE2(z) z != 0 ? (0.4) : (0)
# include "fdf.h"


void (*set_coord[2](t_env, int , int, int) = {set_coord_iso, set_coord_para};

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
				int x_gap;
				int y_gap;
				int x_start;
				int y_start;
				int proj_type;
				int x1;
				int y1;
				int x2;
				int y2;
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
