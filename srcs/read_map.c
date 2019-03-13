/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malavent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 10:22:22 by malavent          #+#    #+#             */
/*   Updated: 2019/03/13 14:09:00 by malavent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/fdf.h"

t_pixel *pushback(int x, int y, char *point, t_pixel *tmp)
{
	if (tmp->next == NULL)
		tmp->next = ft_get_pixel(point, x, y);
	else
		pushback(x, y, point, tmp->next);
	return (tmp);
}

t_pixel *ft_get_line(int y, t_map *map, char *ret_gnl)
{
	t_pixel *tmp;
	t_pixel *begin;
	char 	**tmp_line;
	int x;

	x = 0;
	if (!(tmp_line = ft_strsplit(ret_gnl, ' ')))
		return (NULL);
	if (map->nb_col != ft_strlen_tab(tmp_line))
		return (NULL);
	if (!(tmp = ft_get_pixel(tmp_line[x], x, y)))
		return (NULL);
	begin = tmp;
	x++;
	while (x < map->nb_col)
	{
		if (ft_parsing(tmp_line[x]) == -1)
			return (NULL);
		tmp = pushback(x, y, tmp_line[x], tmp);
		x++;
	}
	return (begin);
}

t_pixel *ft_get_pixel(char *str, int x, int y)
{
	t_pixel *pixel;
	char    *tmp;
	char    *post_coma;

	post_coma = NULL;
	if (ft_strchr(str, ',') != NULL)
		post_coma = ft_strdup(ft_strchr((char const *)str, ',') + 1);
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
	pixel->x = x;
	pixel->y = y;
	return (pixel);
}

t_map *ft_get_map(int fd)
{
	t_map   *map;
	t_pixel *pix_line;
	char    *ret_gnl;
	int     y;

	y  = 0;
	if (!(map = ft_init_map(fd)))
		return (NULL);	
	if (!(pix_line = ft_memalloc(sizeof(t_pixel *))))
		return (NULL);
	lseek(fd, 0, SEEK_SET);
	ft_get_next_line(fd, &ret_gnl);
	if (!(pix_line = ft_get_line(y, map, ret_gnl)))
		return (NULL);
	map->p_alpha = pix_line;
	while ((ft_get_next_line(fd, &ret_gnl) > 0))
	{
		printf("HERE3\n");
		if (!(pix_line = ft_get_line(y, map, ret_gnl)))
			return (NULL);
		while (pix_line)
		{
			printf("%u color : ", pix_line->color);
			pix_line = pix_line->next;
		}
		ft_pxl_pushback((map->p_alpha)->next, pix_line);
		printf("HERE5\n");
		y++;
	}
	printf("HERE6\n");
	ft_strdel(&ret_gnl);
	return (map);
}
