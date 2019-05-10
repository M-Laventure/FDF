#ifndef FDF_H
# define FDF_H
# include "../libft/libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <math.h>
# include "fdf_struct.h"
# include "mlx.h"
# include <stdio.h>
# define USAGE "<usage> : ./fdf target_mapfile"
# define INVALID "Invalid map format"
#define  VALID  "-0123456789xabcdefABCDEF, "

void	free_pix(t_pixel *pixel);
void	set_down(t_env *fdf, t_pixel *cur, void (*set_c[2])(t_env *), int *i);
void	set_right(t_env *fdf, t_pixel *cur, void (*set_c[2])(t_env *), int *i);
void	get_under_node(t_env *fdf, t_map *map, t_pixel *current);
int		key_press(int keycode, void *param);
void	put_menu(t_env *fdf);
void	init_env(t_env *fdf);
int 	init_fdf(t_env *fdf, char *fdf_map);
void	fill_pixel(t_env *fdf, int x, int y, unsigned int hex_color);
void	clear_window(t_env *fdf, int mod);
//void	draw(t_pixel *current, t_env *fdf);
void    draw(t_pixel *current, t_env *fdf);
void	set_coord_iso(t_env *fdf);
void	set_coord_para(t_env *fdf);
//void (set_coord[2](t_env *)) = {set_coord_iso, set_coord_para};
void	segment(t_env *fdf, unsigned int color);
void    fill_pxl(t_env *fdf, int x, int y, int color);
int 	ft_strlen_tab(char **tab);
int     ft_nblines(int fd);
void    ft_tabdel(char ***tab);
int     parsing(char *line);
t_map   *ft_init_map(int fd, t_env *fdf);
t_map   *ft_get_map(int fd, t_env *fdf);
t_pixel *ft_get_line(t_map *map, char *ret_gnl, t_env *fdf);
void	ft_pxl_pushback(t_pixel *begin, t_pixel *maillon);
t_pixel *ft_get_pixel(char *str, t_map *map, t_env *fdf);
t_pixel *ft_init_pix();
t_pixel *pushback(t_env *fdf, t_map *map, char *point, t_pixel *tmp);
void	add_start(t_pixel *start, int gap, int way, int mod);
void	empty_tab(t_env *fdf);
#endif
