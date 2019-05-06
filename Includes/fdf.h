/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brobson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 12:00:08 by brobson           #+#    #+#             */
/*   Updated: 2019/05/03 12:07:16 by brobson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "../libft/libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <math.h>
# include "fdf_struct.h"
# include "mlx.h"

void	put_menu(t_env *fdf);
void	init_env(t_env *fdf);
int 	init_fdf(t_env *fdf, char *fdf_map);
void	fill_pixel(t_env *fdf, int x, int y, unsigned int hex_color);
void	clear_window(t_env *fdf, int mod);
void    draw(t_pixel *current, t_env *fdf);
void	set_coord_iso(t_env *fdf);
void	set_coord_para(t_env *fdf);
void	set_down(t_env *fdf, t_pixel *current, void (*set_coord[2])(t_env *), int *i);
void	set_right(t_env *fdf, t_pixel *current, void (*set_coord[2])(t_env *), int *i);
void	get_under_node(t_env *fdf, t_map *map, t_pixel *current);
int		key_press(int keycode, void *param);
void	segment(t_env *fdf, unsigned int color);
void    fill_pxl(t_env *fdf, int x, int y, int color);
int 	ft_strlen_tab(char **tab);
int     ft_nblines(int fd);
void    ft_tabdel(char **tab);
int     ft_parsing(char *line);
t_map   *ft_init_map(int fd, t_env *fdf);
t_map   *ft_get_map(int fd, t_env *fdf);
t_pixel *ft_get_line(t_map *map, char *ret_gnl, t_env *fdf);
void	ft_pxl_pushback(t_pixel *begin, t_pixel *maillon);
t_pixel *ft_get_pixel(char *str, t_map *map, t_env *fdf);
t_pixel *ft_init_pix();
t_pixel *pushback(t_env *fdf, t_map *map, char *point, t_pixel *tmp);
void	add_start(t_pixel *start, t_env *fdf, int gap, int way, int mod);
void	empty_tab(t_env *fdf);
int     ft_parsing(char *line);

#endif
