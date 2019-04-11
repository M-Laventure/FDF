/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brobson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 16:05:47 by brobson           #+#    #+#             */
/*   Updated: 2019/04/09 17:35:01 by brobson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/fdf.h"

int		ft_img_size(int width, int height)
{
	int size;

	size = width * height;
	return (size);
}

void	add_start(t_pixel *start, int gap, int way, int mod)
{
	if (!start)
		return ;
	if (way == 0)
	{
		start->x += gap * mod;
		add_start(start->next, gap, way, mod);
	}
	else if (way == 1)
	{
		start->y += gap * mod;
		add_start(start->next, gap, way, mod);
	}
	else
	{
		if (start->z != 0)
			start->y += gap * mod;
		add_start(start->next, gap, way, mod);
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

void	set_down(t_env *fdf, t_pixel *current, void (*set_coord[2])(t_env *))
{
	fdf->x1 = current->x;
	fdf->y1 = current->y;
	fdf->z1 = current->z;
	get_under_node(fdf, fdf->map, current);
	set_coord[fdf->proj_type](fdf);
	segment(fdf, current->color);
}

void	set_right(t_env *fdf, t_pixel *current, void (*set_coord[2])(t_env *))
{
	fdf->x1 = current->x;
	fdf->y1 = current->y;
	fdf->z1 = current->z;
	fdf->x2 = (current->next)->x;
	fdf->y2 = (current->next)->y;
	fdf->z2 = (current->next)->z;
	set_coord[fdf->proj_type](fdf);
	segment(fdf, current->color);
}

void	set_coord_para(t_env *fdf)
{
	fdf->x1 = fdf->x1 + CTE1 * fdf->z1;
	fdf->y1 = fdf->y1 + CTE1 / 2 * fdf->z1;
	fdf->x2 = fdf->x2 + CTE1 * fdf->z2;
	fdf->y2 = fdf->y2 + CTE1 / 2 * fdf->z2;
}

void	set_coord_iso(t_env *fdf)
{
	int stock1;
	int stock2;

	stock1 = fdf->x1;
	stock2 = fdf->x2;
	fdf->x1 = (CTE1 * (fdf->x1)) - (CTE2 * (fdf->y1));
	fdf->y1 = fdf->z1 + ((CTE1 / 2) * fdf->x1) + ((CTE2 / 2) * (fdf->y1));
	fdf->x2 = (CTE1 * (fdf->x2)) - (CTE2 * (fdf->y2));
	fdf->y2 = fdf->z2 + ((CTE1 / 2) * fdf->x2) + ((CTE2 / 2) * (fdf->y2));
}

void	draw(t_pixel *current, t_map *map, t_env *fdf)
{
	int j;
	int i;

	i = 1;
	j = 1;
	void (*set_coord[2])(t_env *) = {set_coord_iso, set_coord_para};
	while (current)
	{
		if (i % map->nb_col == 0 && j % map->nb_lines != 0)
		{
			j++;
			set_down(fdf, current, set_coord);
		}
		if (i % map->nb_col != 0 && j % map->nb_lines != 0)
		{
			set_down(fdf, current, set_coord);
			set_right(fdf, current, set_coord);
		}
		if (j % map->nb_lines == 0 && i % map->nb_col != 0)
			set_right(fdf, current, set_coord);
		current = current->next;
		i++;
	}
}

void	fill_pixel(t_env *fdf, int x, int y, int color)
{
	if (y > fdf->height)
		y = (y % fdf->height);
	else if (y < 0)
		y = fdf->height + (y % fdf->height);
	fdf->img_data[(y * fdf->width) + x] = color;
}

void segment(t_env *fdf, int color)
{
	int dx,dy,i,xinc,yinc,cumul,x,y;
	i = 1;
	x = fdf->x1;
	y = fdf->y1;
	dx = fdf->x2 - fdf->x1;
	dy = fdf->y2 - fdf->y1;
	xinc = ( dx > 0 ) ? 1 : -1;
	yinc = ( dy > 0 ) ? 1 : -1;
	dx = abs(dx);
	dy = abs(dy);
	fill_pixel(fdf, x , y, color);
	if (dx > dy)
	{
		cumul = dx / 2;
		while (i <= dx)
		{
			x += xinc;
			cumul += dy;
			if (cumul >= dx)
			{
				cumul -= dx;
				y += yinc;
			}
			fill_pixel(fdf, x , y, color);
			i++;
		}
	}
	else
	{
		cumul = dy / 2;
		while (i <= dy)
		{
			y += yinc;
			cumul += dx;
			if (cumul >= dy)
			{
				cumul -= dy;
				x += xinc;
			}
			fill_pixel(fdf, x , y, color);
			i++;
		}
	}
}
