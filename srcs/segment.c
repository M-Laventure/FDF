/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brobson <brobson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 12:04:53 by brobson           #+#    #+#             */
/*   Updated: 2019/05/18 18:55:01 by brobson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/fdf.h"

static void	init_seg(t_seg *seg, t_env *fdf)
{
	seg->x = fdf->x1;
	seg->y = fdf->y1;
	seg->dx = fdf->x2 - fdf->x1;
	seg->dy = fdf->y2 - fdf->y1;
	seg->xinc = (seg->dx > 0) ? 1 : -1;
	seg->yinc = (seg->dy > 0) ? 1 : -1;
	seg->dx = abs(seg->dx);
	seg->dy = abs(seg->dy);
}

static void	seg_x(t_seg *seg, int *i, t_env *fdf, unsigned int color)
{
	*i += 1;
	seg->cumul = seg->dx / 2;
	while (*i <= seg->dx)
	{
		seg->x += seg->xinc;
		seg->cumul += seg->dy;
		if (seg->cumul >= seg->dx)
		{
			seg->cumul -= seg->dx;
			seg->y += seg->yinc;
		}
		fill_pixel(fdf, seg->x, seg->y, color);
		*i += 1;
	}
}

static void	modif_c(t_seg *seg)
{
	seg->cumul -= seg->dy;
	seg->x += seg->xinc;
}

void		segment(t_env *fdf, unsigned int color)
{
	t_seg	*seg;
	int		i;

	i = 0;
	if (!(seg = (t_seg *)malloc(sizeof(t_seg))))
		return ;
	init_seg(seg, fdf);
	fill_pixel(fdf, seg->x, seg->y, color);
	if (seg->dx > seg->dy)
		seg_x(seg, &i, fdf, color);
	else
	{
		seg->cumul = seg->dy / 2;
		while (++i <= seg->dy)
		{
			seg->y += seg->yinc;
			seg->cumul += seg->dx;
			if (seg->cumul >= seg->dy)
				modif_c(seg);
			fill_pixel(fdf, seg->x, seg->y, color);
		}
	}
	free(seg);
	seg = NULL;
}
