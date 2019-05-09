/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malavent <malavent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 10:22:22 by malavent          #+#    #+#             */
/*   Updated: 2019/05/09 10:48:56 by malavent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/fdf.h"
#include <stdio.h>

t_pixel		*pushback(t_env *fdf, t_map *map, char *point, t_pixel *tmp)
{
	if (tmp->next == NULL)
		tmp->next = ft_get_pixel(point, map, fdf);
	else
		pushback(fdf, map, point, tmp->next);
	return (tmp);
}

void	ft_tabdel(char ***tab)
{
	char **tmp;
	int i;

	tmp = *tab;
	i = 0;
	if (!tab || !tmp)
		return ;
	while (tmp[i])
	{
		ft_strdel(&tmp[i]);
		i++;
	}
	ft_strdel(&tmp[i]);
	free(*tab);
	*tab = NULL;	
	printf("address : %p\n", tab);
}

t_pixel		*ft_get_line(t_map *map, char *ret_gnl, t_env *fdf)
{
	t_pixel		*tmp;
	char		**tmp_line;
	int			i;

	i = 0;
	if (!(tmp_line = ft_strsplit(ret_gnl, ' ')))
		exit(-1);
	ft_tabdel(&tmp_line);	
	return (0);
	if (map->nb_col != ft_strlen_tab(tmp_line))
	{
		ft_putstr("Found wrong line length. Exiting.\n");
		exit(-1);
	}
	if (ft_parsing(tmp_line[i]) == -1)
		exit(-1);
	tmp = ft_get_pixel(tmp_line[i], map, fdf);
	while (++i < map->nb_col)
	{
		if (ft_parsing(tmp_line[i]) == -1)
			exit(-1);
		tmp = pushback(fdf, map, tmp_line[i], tmp);
	}
	printf("this is the adress of la variable1: %p\n", tmp_line);
	ft_tabdel(&tmp_line);
	printf("this is the adress of la variable2: %p\n", tmp_line);

	//printf("this is the adress of la variable3: %p\n", tmp_line);
	return (tmp);
}

void		color_pixel(t_pixel *pixel, char *str)
{
	pixel->z = ft_atoi(str);
	pixel->color = 16777215;
}

t_pixel		*ft_get_pixel(char *str, t_map *map, t_env *fdf)
{
	t_pixel		*pixel;
	char		*tmp;
	char		*post_coma;
	static int	n_pt = 0;

	post_coma = NULL;
	if (!(pixel = ft_init_pix()))
		exit(-1);
	if (ft_strchr(str, ',') != NULL)
	{
		post_coma = ft_strdup(ft_strchr((char const *)str, ',') + 3);
		if (!(tmp = ft_strsub(str, 0, ft_strnlen(str, ','))))
			exit(-1);
		pixel->z = ft_atoi(tmp);
		pixel->color = ft_atoi_base(post_coma, 16, 10);
		ft_strdel(&tmp); //free
		ft_strdel(&post_coma); //free
	}
	else
		color_pixel(pixel, str);
	pixel->x = fdf->x_start + ((n_pt % map->nb_col) * fdf->x_gap);
	pixel->y = fdf->y_start + ((n_pt / map->nb_col) * fdf->y_gap);
	n_pt++;
	return (pixel);	
}

t_map		*ft_get_map(int fd, t_env *fdf)
{
	t_map		*map;
	t_pixel		*pix_line;
	char		*ret_gnl;
	int			y;

	y = 0;
	
	if (!(map = ft_init_map(fd, fdf)))
		exit(-1);
	if (!(pix_line = ft_memalloc(sizeof(t_pixel *))))
		exit(-1);
	close(fd);
	fd = open(fdf->arg, O_RDONLY);
	ft_get_next_line(fd, &ret_gnl);
	if (!(pix_line = ft_get_line(map, ret_gnl, fdf)))
		exit(-1);
	ft_strdel(&ret_gnl);
	map->p_alpha = pix_line;
	while ((ft_get_next_line(fd, &ret_gnl) > 0))
	{
		if (!(pix_line = ft_get_line(map, ret_gnl, fdf)))
			exit(-1);
		ft_pxl_pushback((map->p_alpha)->next, pix_line);
		ft_strdel(&ret_gnl);
		y++;
	}
	return (map);
}
