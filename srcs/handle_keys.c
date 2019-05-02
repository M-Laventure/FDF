#include "../Includes/fdf.h"
#include "stdio.h"

void	handle_color(t_env *fdf, int keycode)
{
	if (keycode == 15)
		fdf->add_color->r += -10;
	else if (keycode == 5)
		fdf->add_color->g += -10;
	else if (keycode == 11)
		fdf->add_color->b += -10;
}

/*
void 	handle_zoom(t_env *fdf, int keycode)
{
	if (keycode == 69)
		fdf->zoom += 1;
	else if (keycode == 78)
		fdf->zoom += -1;
}*/

void	handle_alt(t_env *fdf, int keycode)
{
	if (keycode == 0) // A
		add_start(fdf->map->p_alpha, fdf, fdf->gap_move, 2, -1);
	else if (keycode == 3) // F
		add_start(fdf->map->p_alpha, fdf, fdf->gap_move, 2, 1);
}

void	handle_move(int keycode, t_env *fdf)
{
	if (keycode == 123)
		add_start(fdf->map->p_alpha, fdf, fdf->gap_move, 0, -1);
	else if (keycode == 124)
		add_start(fdf->map->p_alpha, fdf, fdf->gap_move, 0, 1);
	else if (keycode == 125)
		add_start(fdf->map->p_alpha, fdf, fdf->gap_move, 1, 1);
	else if (keycode == 126)
		add_start(fdf->map->p_alpha, fdf, fdf->gap_move, 1, -1);
}

int 	key_press(int keycode, void *param)
{
	t_env *fdf;

	fdf = param;
	if (keycode == 53)
	{
		clear_window(fdf, 1);
		return (0);
	}
	else
		clear_window(fdf, 0);
	if (keycode == 123 || keycode == 124 || keycode == 125 || keycode == 126)
		handle_move(keycode, fdf);
	else if (keycode == 0 || keycode == 3)
		handle_alt(fdf, keycode);
/*	else if (keycode == 69 || keycode == 78)
	{
		handle_zoom(fdf, keycode);
	}*/
	else if (keycode == 15 || keycode == 5 || keycode == 11)
	{
		printf("color\n");
		handle_color(fdf, keycode);
	}
	else if (keycode == 35)
	{
		fdf->proj_type = PROJ(fdf->proj_type);
		if (fdf->proj_type == 0)
		{
			fdf->x_start = fdf->width * 2;
			fdf->y_start = fdf->height * 1.5;
		}
		else if (fdf->proj_type == 1)
		{
			fdf->x_start = fdf->width / 4;
			fdf->y_start = fdf->height / 4;
		}
	}
	draw(fdf->map->p_alpha, fdf);
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->img_ptr, 0, 0);
	put_menu(fdf);
	return (0);
}
