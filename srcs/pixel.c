/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brobson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 16:05:47 by brobson           #+#    #+#             */
/*   Updated: 2019/03/18 15:47:45 by brobson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/fdf.h"

void	fill_pixel(t_env *fdf, int x, int y, int color)
{
	fdf->img_data[(y * fdf->width) + x] = color;
}

void segment(t_env *fdf, int x1, int y1, int x2, int y2)
{
//	printf("x1 : %d y1 : %d x2 : %d y2 : %d\n", x1, y1, x2, y2);
  int dx,dy,i,xinc,yinc,cumul,x,y;
	i = 1;
  x = x1;
  y = y1;
  dx = x2 - x1;
  dy = y2 - y1;
  xinc = ( dx > 0 ) ? 1 : -1;
  yinc = ( dy > 0 ) ? 1 : -1;
  dx = abs(dx);
  dy = abs(dy);
  fill_pixel(fdf, x , y, 0xffffff);
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
			fill_pixel(fdf, x , y, 0xffffff);
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
			fill_pixel(fdf, x , y, 0xffffff);
			i++;
		}
	}
}
