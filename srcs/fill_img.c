#include "../Includes/fdf.h"
#include <stdio.h>

void	hex_to_rgb(unsigned int *hex_color, t_rgb *rgb_color, int mod)
{
	if (mod == 1)
	{
		rgb_color->r = ((*hex_color >> 16) & 0xFF);
		rgb_color->g = ((*hex_color >> 8) & 0xFF);
		rgb_color->b = (*hex_color & 0xFF);
	}
	else
		*hex_color = (rgb_color->r << 16) + (rgb_color->g << 8) + (rgb_color->b);
}


void    fill_pixel(t_env *fdf, int x, int y, unsigned int hex_color)
{
	t_rgb rgb_color;
	hex_to_rgb(&hex_color, &rgb_color, 1);
	rgb_color.r += fdf->add_color->r % 255;
	rgb_color.b += fdf->add_color->b % 255;
	rgb_color.g += fdf->add_color->g % 255;

	rgb_color.r <= 0 ? (rgb_color.r = 254) : (0);	
	rgb_color.r > 255 ? (rgb_color.r = 10) : (0);
	rgb_color.g <= 0 ? (rgb_color.g = 254) : (0);	
	rgb_color.g > 255 ? (rgb_color.g = 10) : (0);
	rgb_color.b <= 0 ? (rgb_color.b = 254) : (0);	
	rgb_color.b > 255 ? (rgb_color.b = 10) : (0);
	hex_to_rgb(&hex_color, &rgb_color, 0);
	if (y > fdf->height)
		y = (y % fdf->height);
	else if (y < 0)
		y = fdf->height + (y % fdf->height);
	fdf->img_data[y * fdf->width + x] = (hex_color == 0xffffff) ? (hex_color) : (hex_color - (y * 1.1));
}
