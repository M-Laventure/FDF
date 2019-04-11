#include "../Includes/fdf.h"

/*void handle_zoom(t_env *fdf, int keycode)
{
	void *img;

	if (keycode == 6)
	{
		mlx_destroy_image(fdf->mlx_ptr, fdf->img_ptr);
		mlx_clear_window(fdf->mlx_ptr, fdf->win_ptr);
		fdf->img_data = (int *)mlx_get_data_addr(fdf->img_ptr, &(fdf->bits_per_pixel), &(fdf->size_line), &(fdf->endian));
		img = mlx_new_image(fdf->mlx_ptr, fdf->width, fdf->height);
		fdf->img_ptr = img;
		fdf->zoom += 5;
		draw(fdf->map->p_alpha, fdf->map, fdf);
		mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->img_ptr, 0, 0);
	}
	else if (keycode == 2)
	{
		mlx_destroy_image(fdf->mlx_ptr, fdf->img_ptr);
		mlx_clear_window(fdf->mlx_ptr, fdf->win_ptr);
		fdf->img_data = (int *)mlx_get_data_addr(fdf->img_ptr, &(fdf->bits_per_pixel), &(fdf->size_line), &(fdf->endian));
		img = mlx_new_image(fdf->mlx_ptr, fdf->width, fdf->height);
		fdf->img_ptr = img;
		fdf->zoom -= 5;
		draw(fdf->map->p_alpha, fdf->map, fdf);
		mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->img_ptr, 0, 0);
	}
}*/

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
	//	printf("HERE1\n");
		start->x = (start->x * cos(fdf->theta) + start->z * sin(fdf->theta));
		start->z = (-stock_x * sin(fdf->theta)) + (start->z * cos(fdf->theta));
	//	printf("HERE2\n");
		rotate_y(start->next, fdf);
	//	printf("HERE3\n");
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
//	mlx_clear_window(fdf->mlx_ptr, fdf->win_ptr);
//	empty_tab(fdf);
	if (keycode == 16)
		rotate_y(fdf->map->p_alpha, fdf);
	if (keycode == 7)
		rotate_x(fdf->map->p_alpha, fdf);
	if (keycode == 6)
		rotate_z(fdf->map->p_alpha, fdf);
	draw(fdf->map->p_alpha, fdf);
}	

void	handle_alt(t_env *fdf, int keycode)
{
	if (keycode == 0)
		add_start(fdf->map->p_alpha, fdf->gap_move, 2, 1);
	else
		add_start(fdf->map->p_alpha, fdf->gap_move, 2, -1);
}

void	handle_move(int keycode, t_env *fdf)
{
	//clear_window(fdf, 0);
	if (keycode == 123)
		add_start(fdf->map->p_alpha, fdf->gap_move, 0, -1);
	else if (keycode == 124)
		add_start(fdf->map->p_alpha, fdf->gap_move, 0, 1);
	else if (keycode == 125)
		add_start(fdf->map->p_alpha, fdf->gap_move, 1, 1);
	else if (keycode == 126)
		add_start(fdf->map->p_alpha, fdf->gap_move, 1, -1);
}

int key_press(int keycode, void *param)
{
	t_env *fdf;
	fdf = param;
	clear_window(fdf, 0);
	if (keycode == 53)
	{
		mlx_destroy_image(fdf->mlx_ptr, fdf->img_ptr);
		mlx_destroy_window(fdf->mlx_ptr, fdf->img_ptr);
		return (0);
	}
	if (keycode == 123 || keycode == 124 || keycode == 125 || keycode == 126)
		handle_move(keycode, fdf);
	else if (keycode == 0 || keycode == 3)
		handle_alt(fdf, keycode);
	else if (keycode == 16 || keycode == 7 || keycode == 6)
		handle_rotation(fdf, keycode);
/*	else if (keycode == 6 || keycode == 2)
		handle_zoom(fdf, keycode);*/
	draw(fdf->map->p_alpha, fdf);
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->img_ptr, 0, 0);
	return (0);
}
