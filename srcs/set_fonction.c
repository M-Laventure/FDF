/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_fonction.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brobson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 11:57:30 by brobson           #+#    #+#             */
/*   Updated: 2019/05/03 11:57:32 by brobson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/fdf.h"

void	set_down(t_env *fdf, t_pixel *current, void (*set_coord[2])(t_env *), int *i)
{
	*i += 0;
	fdf->x1 = current->x;
	fdf->y1 = current->y;
	fdf->z1 = current->z;
	get_under_node(fdf, fdf->map, current);
	set_coord[fdf->proj_type](fdf);
	segment(fdf, current->color);
}

void	set_right(t_env *fdf, t_pixel *current, void (*set_coord[2])(t_env *), int *i)
{
	*i += 0;
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
	fdf->y1 = fdf->y1 + (CTE1 / 2) * fdf->z1;
	fdf->x2 = fdf->x2 + CTE1 * fdf->z2;
	fdf->y2 = fdf->y2 + (CTE1 / 2) * fdf->z2;
}

void	set_coord_iso(t_env *fdf)
{
	int stock1;
	int stock2;

	stock1 = fdf->x1;
	stock2 = fdf->x2;

	fdf->x1 = (fdf->x1 - fdf->y1) * CTE1;
	fdf->y1 = (fdf->x1 + fdf->y1) + (fdf->z1 / CTE2) / 2;
	fdf->x2 = (fdf->x2 - fdf->y2) * CTE1;
	fdf->y2 = (fdf->x2 + fdf->y2) + (fdf->z2 / CTE2) / 2;
}