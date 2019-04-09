/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brobson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 16:05:47 by brobson           #+#    #+#             */
/*   Updated: 2019/03/28 18:13:39 by malavent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/fdf.h"

void	fill_pixel(t_env *fdf, int x, int y, int color)
{
	fdf->img_data[(y * fdf->width) + x] = color;
}

void segment(t_env *fdf, int color)
{
	//	printf("x1 : %d y1 : %d x2 : %d y2 : %d\n", x1, y1, x2, y2);
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
