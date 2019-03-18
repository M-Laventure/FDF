/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brobson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 15:40:21 by brobson           #+#    #+#             */
/*   Updated: 2019/03/18 14:03:25 by brobson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/fdf.h"
#include <stdio.h>

int		ft_img_size(int width, int height)
{
	int size;

	size = width * height;
	return (size);
}

void	draw(t_pixel *current, t_env *fdf)
{
	int x1, y1, x2, y2;
	x1 = 0;
	x2 = 0;
	y1 = 0;
	y2 = 0;
	while (current->next)
	{
		x1 = current->x + (CTE(current->z) * current->z);
		y1 = current->y + ((CTE(current->z) / 2) * current->z);
		x2 = current->next->x + ((CTE(current->z) * current->next->z));
		y2 = current->next->y + ((CTE(current->next->z) / 2) * current->next->z);
		segment(fdf, x1, y1, x2, y2);
		current = current->next;
	}
}

//#####  MAIN FDF #####

int		main(int argc, char **argv)
{
	t_env   fdf;
	t_map   *map;
	int     color;
	int     i;
	int     start_x;
	int     start_y;
	int     fd;

	if (argc != 2)
		return (-1);
	if ((fd = open(argv[1], O_RDONLY)) == -1)
		return (-1);
	i = 0;
	// tools 
	map = ft_get_map(fd, &fdf);
	if (!map)
		return (1);
	while (map->p_alpha)
	{
		if (i % (map->nb_col) == 0 && i != 0)
			printf("\n");
		printf("%d", map->p_alpha->z);
		printf(",%u", map->p_alpha->color);
		if (map->p_alpha->next && map->p_alpha->next->z == 50)
			printf(" ");
		else if (map->p_alpha->next && (map->p_alpha->z == 0 || map->p_alpha->z == 50) && (map->p_alpha->next->z == 0))
			printf("  ");
		map->p_alpha = (map->p_alpha)->next;
		i++;
	}
	// tools
	start_x = 0;
	start_y = 0;
	color = 0xff0000;
	fdf.width = 1300;
	fdf.height = 800;
	fdf.size_img = fdf.width * fdf.height;
	fdf.mlx_ptr = mlx_init();
	fdf.win_ptr = mlx_new_window(fdf.mlx_ptr, fdf.width, fdf.height, "fdf");
	fdf.img_ptr = mlx_new_image(fdf.mlx_ptr, fdf.width, fdf.height);
	fdf.img_data = (unsigned int *)mlx_get_data_addr(fdf.img_ptr, &fdf.bits_per_pixel, &fdf.size_line , &fdf.endian);
	//draw( , &fdf);
	mlx_put_image_to_window(fdf.mlx_ptr, fdf.win_ptr, fdf.img_ptr, 0 ,0);
	close(fd);
	mlx_loop(fdf.mlx_ptr);
	return (0);
}
