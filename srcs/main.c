/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brobson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 15:40:21 by brobson           #+#    #+#             */
/*   Updated: 2019/05/01 18:38:37 by malavent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/fdf.h"
#include <stdio.h>

void	init_mlx(t_env *fdf)
{
	fdf->mlx_ptr = mlx_init();
	fdf->win_ptr = mlx_new_window(fdf->mlx_ptr, fdf->width, fdf->height, "WireFrame");
	fdf->img_ptr = mlx_new_image(fdf->mlx_ptr, fdf->width, fdf->height);
	fdf->img_data = (unsigned int *)mlx_get_data_addr(fdf->img_ptr, &fdf->bpp, &fdf->size_line, &fdf->endian);
}

void init_fdf(t_env *fdf)
{
	fdf->gap_move = 10;
	fdf->zoom = 0;
	fdf->width = 2560;
	fdf->height = 1440;
	fdf->x_start = fdf->width / 2;
	fdf->y_start = fdf->height / 2;
	fdf->img_xstart = 0;
	fdf->img_ystart = 0;
	fdf->proj_type = 1;
	fdf->x1 = 0;
	fdf->x2 = 0;
	fdf->y1 = 0;
	fdf->y2 = 0;
	fdf->z1 = 0;
	fdf->z2 = 0;
	fdf->size_img = fdf->width * fdf->height;
	init_mlx(fdf);
	fdf->add_color = (t_rgb *)malloc(sizeof(t_rgb));
}

int		main(int argc, char **argv)
{
	t_env   fdf;
	t_map *map;
	int     fd;

	if (argc != 2)
	{
		ft_putendl("error");
		return (-1);
	}
	if ((fd = open(argv[1], O_RDONLY)) == -1)
		return (-1);
	close(fd);
/*	printf("x1: %d\n", fdf.x1);
	printf("y1: %d\n", fdf.y1);
	printf("x_start: %d\n", fdf.x_start);
	printf("y_start: %d\n", fdf.y_start);
	printf("proj_type: %d\n", fdf.proj_type);
	printf("gap_move: %d\n", fdf.y1);
	printf(": %d\n", fdf.y1);*/

	init_fdf(&fdf);
	if (!(map = ft_get_map(fd, &fdf)))
		return (-1);
	fdf.map = map;
	printf("imgstartx: %d\n", fdf.img_xstart);
	printf("imgstarty: %d\n", fdf.img_ystart);
	draw(fdf.map->p_alpha, &fdf);
	printf("imgstarty: %d\n", fdf.img_ystart);
	mlx_put_image_to_window(fdf.mlx_ptr, fdf.win_ptr, fdf.img_ptr, fdf.img_xstart, fdf.img_ystart);
	put_menu(&fdf);
	mlx_hook(fdf.win_ptr, 2, 1L << 0, key_press, &fdf);
	mlx_loop(fdf.mlx_ptr);
	return (0);
}
