/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brobson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 15:40:21 by brobson           #+#    #+#             */
/*   Updated: 2019/04/11 20:09:29 by malavent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/fdf.h"
#include <stdio.h>

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
	fdf.x_gap = 30;
	fdf.y_gap = 30;
	fdf.gap_move = 10;
	fdf.zoom = 0;
	fdf.width = 1000;
	fdf.height = 1000;
	fdf.proj_type = 0;
	fdf.x1 = 0;
	fdf.x2 = 0;
	fdf.y1 = 0;
	fdf.y2 = 0;
	fdf.z1 = 0;
	fdf.z2 = 0;
	fdf.theta = 90;
	fdf.size_img = fdf.width * fdf.height;
	fdf.mlx_ptr = mlx_init();
	fdf.win_ptr = mlx_new_window(fdf.mlx_ptr, fdf.width, fdf.height, "fdf");
	fdf.img_ptr = mlx_new_image(fdf.mlx_ptr, fdf.width, fdf.height);
	fdf.img_data = (int *)mlx_get_data_addr(fdf.img_ptr, &fdf.bits_per_pixel, &fdf.size_line , &fdf.endian);
	if (!(map = ft_get_map(fd, &fdf)))
		return (-1);
	fdf.map = map;
	/*printf("map_size%d\n", map->map_size);
	  while (map->p_alpha)
	  {
	  if (i % (map->nb_col) == 0 && i != 0)
	  printf("\n");
	  printf("x%d : %d ", k, map->p_alpha->x);
	  printf("y%d : %d -", k, map->p_alpha->y);
	  printf(" ");
	  map->p_alpha = (map->p_alpha)->next;
	  k++;
	  i++;

	  }*/
	draw(fdf.map->p_alpha, &fdf);
	mlx_put_image_to_window(fdf.mlx_ptr, fdf.win_ptr, fdf.img_ptr, 0 ,0);
	close(fd);
	mlx_hook(fdf.win_ptr, 2, 1L << 0, key_press, &fdf);
	mlx_loop(fdf.mlx_ptr);
	return (0);
}
