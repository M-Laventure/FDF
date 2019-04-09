/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malavent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 10:22:22 by malavent          #+#    #+#             */
/*   Updated: 2019/04/09 17:01:43 by malavent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/fdf.h"

t_pixel *pushback(t_env *fdf, t_map *map, char *point, t_pixel *tmp)
{
	if (tmp->next == NULL)
		tmp->next = ft_get_pixel(point, map, fdf);
	else
		pushback(fdf, map, point, tmp->next);
	return (tmp);
}

t_pixel *ft_get_line(t_map *map, char *ret_gnl, t_env *fdf)
{
	t_pixel *tmp;
	t_pixel *begin;
	char 	**tmp_line;
	int i;

	i = 0;
	if (!(tmp_line = ft_strsplit(ret_gnl, ' ')))
		return (NULL);
	if (map->nb_col != ft_strlen_tab(tmp_line))
	{
		ft_putstr("Found wrong line length. Exiting.\n");
		return (NULL);
	}
	if (ft_parsing(tmp_line[i]) == -1)
		return (NULL);
	if (!(tmp = ft_get_pixel(tmp_line[i], map, fdf)))
		return (NULL);
	begin = tmp;
	i++;
	while (i < map->nb_col)
	{
		if (ft_parsing(tmp_line[i]) == -1)
			return (NULL);
		tmp = pushback(fdf, map, tmp_line[i], tmp);
		i++;
	}
	return (begin);
}

t_pixel *ft_get_pixel(char *str, t_map *map, t_env *fdf)
{
	t_pixel 	*pixel;
	char    	*tmp;
	char    	*post_coma;
	static int	n_pt = 0;

	post_coma = NULL;
	if (ft_strchr(str, ',') != NULL)
		post_coma = ft_strdup(ft_strchr((char const *)str, ',') + 3);
	if (!(pixel = ft_init_pix()))
		return (NULL);
	if (post_coma != NULL)
	{
		if (!(tmp = ft_strsub(str, 0, ft_strnlen(str, ','))))
			return (NULL);
		pixel->z = ft_atoi(tmp);
		ft_strdel(&tmp);
		pixel->color = ft_atoi_base(post_coma, 16, 10);
	}
	else
	{
		pixel->z = ft_atoi(str);
		pixel->color = 16777215;
	}
	pixel->x = fdf->x_start + ((n_pt % map->nb_col) * fdf->x_gap);
   	pixel->y = fdf->y_start + ((n_pt / map->nb_col) * fdf->y_gap);
	n_pt++;
	return (pixel);
}

t_map *ft_get_map(int fd, t_env *fdf)
{
	t_map   *map;
	t_pixel *pix_line;
	char    *ret_gnl;
	int     y;

	y  = 0;
	if (!(map = ft_init_map(fd, fdf)))
		return (NULL);	
	if (!(pix_line = ft_memalloc(sizeof(t_pixel *))))
		return (NULL);
	lseek(fd, 0, SEEK_SET);
	ft_get_next_line(fd, &ret_gnl);
	if (!(pix_line = ft_get_line(map, ret_gnl, fdf)))
		return (NULL);
	map->p_alpha = pix_line;
	while ((ft_get_next_line(fd, &ret_gnl) > 0))
	{
		if (!(pix_line = ft_get_line(map, ret_gnl, fdf)))
			return (NULL);
		ft_pxl_pushback((map->p_alpha)->next, pix_line);
		y++;
	}
	ft_strdel(&ret_gnl);
	return (map);
}
