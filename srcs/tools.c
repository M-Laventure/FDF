/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brobson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 13:54:02 by brobson           #+#    #+#             */
/*   Updated: 2019/05/02 20:06:30 by malavent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/fdf.h"

void	put_menu(t_env *fdf)
{
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 0, 0, 0xffd700, ARROWS);
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 0, 20, 0xffd700, ZOOM);
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 0, 40, 0xffd700, SWITCH);
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 0, 60, 0xffd700, COLORS);
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 0, 80, 0xffd700, Z);	
}

void	clear_window(t_env *fdf, int mod)
{
	mlx_clear_window(fdf->mlx_ptr, fdf->win_ptr);
	empty_tab(fdf);
	if (mod == 1)
		mlx_destroy_window(fdf->mlx_ptr, fdf->win_ptr);
}

int ft_strlen_tab(char **tab)
{
	int i;

	i = 0;
	while (tab[i] != 0)
		i++;
	return (i);
}

int  ft_nblines(int fd)
{
	int nb_lines;
	int r;
	char *line;

	nb_lines = 0;
	while ((r = ft_get_next_line(fd, &line)) > 0)
		nb_lines++;
	return (nb_lines);
}

t_pixel *ft_init_pix(void)
{
	t_pixel *new;

	if (!(new = (t_pixel *)malloc(sizeof(t_pixel))))
		return (NULL);
	ft_bzero(new, sizeof(t_pixel));
	new->next = NULL;
	return (new);
}

void ft_tabdel(char **tab)
{
	if (!tab)
		return ;
	while (*tab)
	{
		free(*tab);
		tab++;
	}
	free(tab);
	tab = NULL;
}

void ft_pxl_pushback(t_pixel *begin, t_pixel *node)
{
	if (begin->next == NULL)
		begin->next = node;
	else
		ft_pxl_pushback(begin->next, node);	
}

t_map *ft_init_map(int fd, t_env *fdf)
{
	t_map *map;
	t_pixel *p_alpha;
	char *line;
	char **tmp_line;

	line = 0;
	ft_get_next_line(fd, &line);
	if (!(tmp_line = ft_strsplit(line, ' ')))
		return (NULL);
	if (!(map = (t_map *)malloc(sizeof(t_map))) || !(p_alpha = ft_init_pix()))
		return (NULL);
	map->nb_lines = ft_nblines(fd) + 1;
	map->nb_col =  ft_strlen_tab(tmp_line);
	map->map_size = map->nb_lines * map->nb_col;
	fdf->x_gap = 800 / map->nb_col;
	fdf->y_gap = fdf->x_gap;
	map->p_alpha = p_alpha;
	map->p_alpha->x = fdf->x_start;
	map->p_alpha->y = fdf->y_start;
	map->p_alpha->next = NULL;
	ft_strdel(&line);
	return (map);
}

void    empty_tab(t_env *fdf)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (x < fdf->width)
	{
		while (y < fdf->height)
		{
			fdf->img_data[(y * fdf->width) + x] = 0;
			y++;
		}
		y = 0;
		x++;
	}
}