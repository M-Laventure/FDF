#ifndef FDF_STRUCT_H
# define FDF_STRUCT_H
# define PROJ(x) x == 1 ? (0) : (1)
# define CTE1 0.5
# define CTE2 0.5 
# define MENU "move : [arrow keys]\nZoom : [+/-]\nSwitch proj: [p], Change colors: [r, g , b]\nIncrease or Decrease z [a, f]"
# include "fdf.h"

typedef struct s_rgb
{
	int r;
	int g;
	int b;
}				t_rgb;

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
                int gap_move;
                int zoom;
				int theta;
                int size_line;
                int width;
                int height;
                int img_width;
                int img_height;
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
				t_rgb *add_color;
}               t_env;

#endif
