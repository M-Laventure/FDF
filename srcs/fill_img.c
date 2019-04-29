#include "../Includes/fdf.h"
#include <stdio.h>

void	hex_to_rgb(unsigned int hex_color, t_rgb *rgb_color, char *mod)
{
	if (ft_strcmp(mod, "to_rgb") == 0)
	{	
		rgb_color->r = ((hex_color >> 16) & 0xFF) / 255.0;
		rgb_color->g = ((hex_color >> 8) & 0xFF) / 255.0;
		rgb_color->b = (hex_color & 0xFF) / 255;
	}
	else
	{
		hex_color = (rgb_color->r & 0xff << 16) + (rgb_color->g & 0xff << 8) + (rgb_color->b & 0xff);
	}
}


void    fill_pixel(t_env *fdf, int x, int y, unsigned int hex_color)
{
/*	t_rgb *rgb_color;

	rgb_color = ft_memalloc(sizeof(rgb_color));
	hex_to_rgb(hex_color, rgb_color, "to_rgb");
	rgb_color->r += fdf->add_color->r;
	rgb_color->b += fdf->add_color->b;
	rgb_color->g += fdf->add_color->g;

	printf("r : [%d]\n", rgb_color->r);
	printf("b : [%d]\n", rgb_color->b);
	printf("g : [%d]\n", rgb_color->g);
	hex_to_rgb(hex_color, rgb_color, "to_hex");*/
	if (y > fdf->height)
		y = (y % fdf->height);
	else if (y < 0)
		y = fdf->height + (y % fdf->height);
    fdf->img_data[y * fdf->width + x] = hex_color;
}
