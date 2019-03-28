/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brobson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 13:54:02 by brobson           #+#    #+#             */
/*   Updated: 2019/03/26 11:33:18 by malavent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/fdf.h"

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
	tmp_line = ft_strsplit(line, ' ');
	if (!(map = (t_map *)malloc(sizeof(t_map))) || !(p_alpha = ft_init_pix()))
		return (NULL);
	map->nb_lines = ft_nblines(fd);
	map->nb_col =  ft_strlen_tab(tmp_line);
	map->map_size = map->nb_lines * map->nb_col;
	map->p_alpha = p_alpha;
	map->p_alpha->x = fdf->x_start;
	map->p_alpha->y = fdf->y_start;
	map->p_alpha->next = NULL;
	ft_strdel(&line);
//	ft_tabdel(tmp_line);
	return (map);
}

int ft_parsing(char *line)
{
	char 	*post_coma;
	char	*pre_coma;
	int		len;
	int		i;
	
	len = 0;
	i = 0;
	if (ft_strchr(line, ',') != NULL)
	{
		if (!(post_coma = ft_strdup(ft_strchr(line, ',') + 3)))
			return (-1);
		while (line[i++] != ',')
			len++;
		i = 0;
		if (!(pre_coma = ft_strsub(line, 0, len)))
			return (-1);
	}
	if (ft_strchr(line, ',') == NULL)
	{
		while (pre_coma[i])
		{
			if (ft_isdigit(ft_atoi(&pre_coma[i++]) == 0))
				return (-1);
		}
		return (1);
	}
	else
	{
		while (pre_coma[i])
		{
			if (ft_isdigit(ft_atoi(&pre_coma[i++]) == 0))
				return (-1);
		}
		if (line[len] != ',' || (line[len + 1] != '0' && line[len + 2] != 'x'))
			return (-1);
		while (*post_coma)
		{
			if (!ft_is_inbase(16, *post_coma))
				return (-1);
			post_coma++;
		}
	}
	return (1);
}
