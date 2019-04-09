/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brobson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 15:40:21 by brobson           #+#    #+#             */
/*   Updated: 2019/04/09 17:33:32 by brobson          ###   ########.fr       */
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
	// tools 
	i = 0;
	k = 1;
	// tools
	fdf.x_start = 500;
	fdf.y_start = 500;
	fdf.x_gap = 50;
	fdf.y_gap = 50;
	fdf.width = 2160;
	fdf.height = 1440;
	fdf.proj_type = 0;
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
	map = ft_get_map(fd, &fdf);
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
	draw(map->p_alpha, map, &fdf);
	mlx_put_image_to_window(fdf.mlx_ptr, fdf.win_ptr, fdf.img_ptr, 0 ,0);
	close(fd);
	mlx_loop(fdf.mlx_ptr);
	return (0);
}
