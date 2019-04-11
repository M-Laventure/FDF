/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brobson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 15:40:21 by brobson           #+#    #+#             */
/*   Updated: 2019/04/09 17:39:56 by brobson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/fdf.h"
#include <stdio.h>

void new_alt(t_env *fdf, int keycode)
{
	mlx_clear_window(fdf->mlx_ptr, fdf->win_ptr);
	empty_tab(fdf);
	if (keycode == 0)
		add_start(fdf->map->p_alpha, fdf->gap_move, 2, 1);
	else
		add_start(fdf->map->p_alpha, fdf->gap_move, 2, -1);
	draw(fdf->map->p_alpha, fdf->map, fdf);
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->img_ptr, 0, 0);
}

int key_press(int keycode, void *param)
{
	t_env *fdf;

	fdf = param;
	if (keycode == 53)
	{
		mlx_destroy_image(fdf->mlx_ptr, fdf->img_ptr);
		mlx_clear_window(fdf->mlx_ptr, fdf->win_ptr);
		mlx_destroy_window(fdf->mlx_ptr, fdf->win_ptr);
		return (0);
	}
	if (keycode == 123)
	{
		mlx_clear_window(fdf->mlx_ptr, fdf->win_ptr);
		empty_tab(fdf);
		add_start(fdf->map->p_alpha, fdf->gap_move, 0, -1);
		draw(fdf->map->p_alpha, fdf->map, fdf);
		mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->img_ptr, 0, 0);
	}
	else if (keycode == 124)
	{
		mlx_clear_window(fdf->mlx_ptr, fdf->win_ptr);
		empty_tab(fdf);
		add_start(fdf->map->p_alpha, fdf->gap_move, 0, 1);
		draw(fdf->map->p_alpha, fdf->map, fdf);
		mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->img_ptr, 0, 0);	
	}
	else if (keycode == 125)
	{
		mlx_clear_window(fdf->mlx_ptr, fdf->win_ptr);
		empty_tab(fdf);
		add_start(fdf->map->p_alpha, fdf->gap_move, 1, 1);
		draw(fdf->map->p_alpha, fdf->map, fdf);
		mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->img_ptr, 0, 0);
	}
	else if (keycode == 126)
	{
		mlx_clear_window(fdf->mlx_ptr, fdf->win_ptr);
		empty_tab(fdf);
		add_start(fdf->map->p_alpha, fdf->gap_move, 1, -1);
		draw(fdf->map->p_alpha, fdf->map, fdf);
		mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->img_ptr, 0, 0);
	}
	/*else if (keycode == 6 || keycode == 2)
		zoom(fdf, keycode);*/
	else if (keycode == 0 || keycode == 3)
		new_alt(fdf, keycode);
	return (0);
}

int		main(int argc, char **argv)
{
	t_env   fdf;
	t_map   *map;
	int     i;
	int     fd;
	int		k;

	if (argc != 2)
	{
		ft_putendl("error");
		return (-1);
	}
	if ((fd = open(argv[1], O_RDONLY)) == -1)
		return (-1);
	i = 0;
	k = 1;
	fdf.x_start = 500;
	fdf.y_start = 500;
	fdf.x_gap = 10;
	fdf.y_gap = 10;
	fdf.gap_move = 10;
	fdf.zoom = 0;
	fdf.width = 1000;
	fdf.height = 1000;
	fdf.proj_type = 1;
	fdf.x1 = 0;
	fdf.x2 = 0;
	fdf.y1 = 0;
	fdf.y2 = 0;
	fdf.z1 = 0;
	fdf.z2 = 0;
	fdf.size_img = fdf.width * fdf.height;
	fdf.mlx_ptr = mlx_init();
	fdf.win_ptr = mlx_new_window(fdf.mlx_ptr, fdf.width, fdf.height, "fdf");
	fdf.img_ptr = mlx_new_image(fdf.mlx_ptr, fdf.width, fdf.height);
	fdf.img_data = (unsigned int *)mlx_get_data_addr(fdf.img_ptr, &fdf.bits_per_pixel, &fdf.size_line , &fdf.endian);
	if (!(map = ft_get_map(fd, &fdf)))
		return (-1);
	fdf.map = map;
	draw(fdf.map->p_alpha, map, &fdf);
	mlx_put_image_to_window(fdf.mlx_ptr, fdf.win_ptr, fdf.img_ptr, 0 ,0);
	close(fd);
	mlx_hook(fdf.win_ptr, 2, 1L << 0, key_press, &fdf);
	mlx_loop(fdf.mlx_ptr);
	return (0);
}
