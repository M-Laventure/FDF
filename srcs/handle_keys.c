#include "../Includes/fdf.h"
#include "stdio.h"

void 	handle_zoom(t_env *fdf, int keycode)
{
	if (keycode == 6)
		fdf->zoom += 2;
	else if (keycode == 2)
		fdf->zoom -= 2;
}

void	rotate_x(t_pixel *start, t_env *fdf)
{
	int stock_y;

	stock_y = start->y;
	if (!start)
		return ;
	else
	{
		start->y *= cos(fdf->theta) + start->z * sin(fdf->theta);
		start->z = (-stock_y * sin(fdf->theta)) + (start->z * cos(fdf->theta));
		rotate_x(start->next, fdf);
	}
}

void	rotate_y(t_pixel *start, t_env *fdf)
{
	int stock_x;

	stock_x = start->x;
	if (!start->next)
		return ;
	else
	{
		start->x = (start->x * cos(fdf->theta) + start->z * sin(fdf->theta));
		start->z = (-stock_x * sin(fdf->theta)) + (start->z * cos(fdf->theta));
		rotate_y(start->next, fdf);
	}
}

void	rotate_z(t_pixel *start, t_env *fdf)
{
	int stock_x;
	
	stock_x = start->x;
	if (!start)
		return ;
	else
	{
		start->x = (start->x * cos(fdf->theta)) + start->x - start->y * sin(fdf->theta);
		start->y = (start->x * sin(fdf->theta)) + (start->y * cos(fdf->theta));
		rotate_z(start->next, fdf);
	}
}

void	handle_rotation(t_env *fdf, int keycode)
{
	if (keycode == 16) // Y
		rotate_y(fdf->map->p_alpha, fdf);
	if (keycode == 7) // X
		rotate_x(fdf->map->p_alpha, fdf);
	if (keycode == 6) // Z
		rotate_z(fdf->map->p_alpha, fdf);
	draw(fdf->map->p_alpha, fdf->map, fdf);
}

void	handle_alt(t_env *fdf, int keycode)
{
	if (keycode == 0) // A
		add_start(fdf->map->p_alpha, fdf->gap_move, 2, 1);
	else if (keycode == 3) // F
		add_start(fdf->map->p_alpha, fdf->gap_move, 2, -1);
}

void	handle_move(int keycode, t_env *fdf)
{
	if (keycode == 123)
		add_start(fdf->map->p_alpha, fdf->gap_move, 0, -1);
	else if (keycode == 124)
		add_start(fdf->map->p_alpha, fdf->gap_move, 0, 1);
	else if (keycode == 125)
		add_start(fdf->map->p_alpha, fdf->gap_move, 1, 1);
	else if (keycode == 126)
		add_start(fdf->map->p_alpha, fdf->gap_move, 1, -1);
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
	{
		//printf("avant gauche\n");
		handle_move(keycode, fdf);
		//printf("apres gauche\n");
	}
	else if (keycode == 0 || keycode == 3)
		handle_alt(fdf, keycode);
	else if (keycode == 16 || keycode == 7 || keycode == 8)
		handle_rotation(fdf, keycode);
	else if (keycode == 6 || keycode == 2)
		handle_zoom(fdf, keycode);
	//printf("avant draww\n");
	draw(fdf->map->p_alpha, fdf->map, fdf);
	//printf("apres draww\n");
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->img_ptr, 0, 0);
	return (0);
}
