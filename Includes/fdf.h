#ifndef FDF_H
#define FDF_H
#include "mlx.h"
#include "fdf_struct.h"
#include "../libft/libft.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#define RED = 0xff0000

void    fill_pxl(t_env *fdf, int x, int y, int color);
int     ft_strlen_tab(char **tab);
int     ft_nblines(int fd);
void    ft_tabdel(char **tab);
int     ft_parsing(char *line);
t_map   *ft_init_map(int fd);
t_map   ft_get_map(int fd);
t_pixel *ft_get_line(int y, t_pixel *pix_line, char *ret_gnl);
t_pixel *ft_get_pixel(char *str, int x, int y);

#endif