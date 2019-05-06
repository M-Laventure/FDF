/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brobson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 16:05:47 by brobson           #+#    #+#             */
/*   Updated: 2019/05/02 20:08:37 by malavent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/fdf.h"

void	add_start(t_pixel *start, t_env *fdf, int gap, int mod, int way)
{
	if (!start)
		return ;
	if (mod == 0)
	{
		start->x += gap * way;
		add_start(start->next, fdf, gap, mod, way);
	}
	else if (mod == 1)
	{
		start->y += gap * way;
		add_start(start->next, fdf, gap, mod, way);
	}
	else
	{
		start->y += gap * (start->z * 0.2) * way;
		add_start(start->next, fdf, gap, mod, way);
	}
}

void	get_under_node(t_env *fdf, t_map *map, t_pixel *current)
{
	static int k = 1;

	if ((k % (map->nb_col + 1) == 0) && current)
	{
		fdf->x2 = current->x;
		fdf->y2 = current->y;
		fdf->z2 = current->z;
		k = 1;
		return ;
	}
	if (!current)
		return ;
	k++;
	get_under_node(fdf, map, current->next);
}

void    draw(t_pixel *current, t_env *fdf)
{
    int j;
    int i;
	void (*set_coord[2])(t_env *) = {set_coord_iso, set_coord_para};

    i = 1;
    j = 1;
    while (current)
    {
        if (i % fdf->map->nb_col == 0 && j % fdf->map->nb_lines != 0)
        {
            j++;
            set_down(fdf, current, set_coord, &i);
        }
        if (i % fdf->map->nb_col != 0 && j % fdf->map->nb_lines != 0)
        {
            set_down(fdf, current, set_coord, &i);
        	set_right(fdf, current, set_coord, &i);
        }
        if (j % fdf->map->nb_lines == 0 && i % fdf->map->nb_col != 0)
            set_right(fdf, current, set_coord, &i);
        current = current->next;
        i++;
    }
	i = 0;
}