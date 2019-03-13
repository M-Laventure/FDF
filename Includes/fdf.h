#ifndef FDF_H
#define FDF_H
#include "../libft/libft.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include "fdf_struct.h"
#include "mlx.h"

#define RED = 0xff0000

void    fill_pxl(t_env *fdf, int x, int y, int color);
int  ft_strlen_tab(char **tab);
int     ft_nblines(int fd);
void    ft_tabdel(char **tab);
int     ft_parsing(char *line);
t_map   *ft_init_map(int fd);
t_map   *ft_get_map(int fd);
t_pixel *ft_get_line(int y, t_map *map, char *ret_gnl);
void	ft_pxl_pushback(t_pixel *begin, t_pixel *maillon);
t_pixel *ft_get_pixel(char *str, int x, int y);
t_pixel *ft_init_pix();

#endif
