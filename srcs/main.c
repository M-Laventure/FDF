/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malavent <malavent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 15:40:21 by brobson           #+#    #+#             */
/*   Updated: 2019/05/09 11:41:29 by malavent         ###   ########.fr       */
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


void init_env/*fdf*/(t_env *fdf)
{
	fdf->gap_move = 10;
	fdf->zoom = 0;
	fdf->width = 2560;
	fdf->height = 1440;
	fdf->x_start = fdf->width * 2;
	fdf->y_start = fdf->height * 1.5;
	fdf->x_gap = 0;
	fdf->y_gap = 0;
	fdf->x1 = 0;
	fdf->x2 = 0;
	fdf->y1 = 0;
	fdf->y2 = 0;
	fdf->z1 = 0;
	fdf->z2 = 0;
	fdf->size_img = fdf->width * fdf->height;
	if (!(fdf->add_color = (t_rgb *)malloc(sizeof(t_rgb))))
		exit(1);
	ft_bzero(fdf->add_color, sizeof(t_rgb));
}

int init_fdf(t_env *fdf, char *fdf_map)
{
	t_map *map;
	int fd;

	init_env(fdf);
	init_mlx(fdf);
	fdf->proj_type = 0;
	fdf->arg = ft_strdup(fdf_map);
	if ((fd = open(fdf->arg, O_RDONLY)) == -1)
		exit(-1);
	fdf->fd = fd;
	if (!(map = ft_get_map(fd, fdf)))
		exit(-1);
	fdf->map = map;
	close(fd);
	return (1);
}

int		main(int argc, char **argv)
{
	t_env   fdf;

	if (argc != 2)
	{
		ft_putendl(USAGE);
		return (-1);
	}
	if (!(init_fdf(&fdf, argv[1])))
	{
		ft_putendl("An error occured");
		return (-1);
	}
	draw(fdf.map->p_alpha, &fdf);
	mlx_put_image_to_window(fdf.mlx_ptr, fdf.win_ptr, fdf.img_ptr, 0, 0);
	put_menu(&fdf);
	mlx_hook(fdf.win_ptr, 2, 1L << 0, key_press, &fdf);
	mlx_loop(fdf.mlx_ptr);
	return (0);
}
