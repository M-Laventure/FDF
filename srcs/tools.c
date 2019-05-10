/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malavent <malavent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 13:54:02 by brobson           #+#    #+#             */
/*   Updated: 2019/05/09 09:31:43 by malavent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/fdf.h"
#include <stdio.h>

void	ft_pxl_pushback(t_pixel *begin, t_pixel *node)
{
	if (begin->next == NULL)
		begin->next = node;
	else
		ft_pxl_pushback(begin->next, node);
}

t_map	*ft_init_map(int fd, t_env *fdf)
{
	t_map		*map;
	t_pixel		*p_alpha;
	char		*line;
	char		**tmp_line;

	line = 0;
	ft_get_next_line(fd, &line);
	if (!(tmp_line = ft_strsplit(line, ' ')))
		exit(-1);
	if (!(map = (t_map *)malloc(sizeof(t_map))))
		exit(-1);
	if (!(p_alpha = ft_init_pix()))
		exit(-1);
	map->nb_lines = ft_nblines(fd) + 1;
	map->nb_col = ft_strlen_tab(tmp_line);
	map->map_size = map->nb_lines * map->nb_col;
	fdf->x_gap = 800 / map->nb_col;
	fdf->y_gap = fdf->x_gap;
	map->p_alpha = p_alpha;
	map->p_alpha->x = fdf->x_start;
	map->p_alpha->y = fdf->y_start;
	map->p_alpha->next = NULL;
	ft_strdel(&line);
	ft_tabdel(&tmp_line);
	return (map);
}

void	empty_tab(t_env *fdf)
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
