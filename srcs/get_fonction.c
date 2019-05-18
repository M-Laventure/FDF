/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fonction.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brobson <brobson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 18:58:03 by brobson           #+#    #+#             */
/*   Updated: 2019/05/18 18:59:59 by brobson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/fdf.h"

t_map		*ft_get_map(int fd, t_env *fdf)
{
	t_map		*map;
	t_pixel		*pix_line;
	char		*ret_gnl;
	int			y;

	y = 0;
	pix_line = NULL;
	if (!(map = ft_init_map(fd, fdf)))
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
