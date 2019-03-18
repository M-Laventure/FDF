#ifndef FDF_H
# define FDF_H
# include "../libft/libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include "fdf_struct.h"
# include "mlx.h"
# define RED = 0xff0000


void	segment(t_env *fdf, int x1, int y1, int x2, int y2);
void    fill_pxl(t_env *fdf, int x, int y, int color);
int 	ft_strlen_tab(char **tab);
int     ft_nblines(int fd);
void    ft_tabdel(char **tab);
int     ft_parsing(char *line);
t_map   *ft_init_map(int fd, t_env *fdf);
t_map   *ft_get_map(int fd, t_env *fdf);
t_pixel *ft_get_line(t_map *map, char *ret_gnl, t_env *fdf);
void	ft_pxl_pushback(t_pixel *begin, t_pixel *maillon);
t_pixel *ft_get_pixel(char *str, t_env *fdf);
t_pixel *ft_init_pix();
void	fill_pixel(t_env *fdf, int x, int y, int color);
void    draw(t_pixel *current, t_env *fdf);

#endif
