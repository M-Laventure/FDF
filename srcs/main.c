/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brobson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 15:40:21 by brobson           #+#    #+#             */
/*   Updated: 2019/03/18 16:17:01 by brobson          ###   ########.fr       */
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
	int x1, y1, x2, y2, i;
	i = -1;
	x1 = 0;
	x2 = 0;
	y1 = 0;
	y2 = 0;
	while (current->next)
	{
		//printf("current x : %d\n", current->x);
		x1 = current->x + (CTE(current->z) * current->z);
		y1 = current->y + ((CTE(current->z) / 2) * current->z);
		x2 = current->next->x + ((CTE(current->z) * current->next->z));
		y2 = current->next->y + ((CTE(current->next->z) / 2) * current->next->z);
		segment(fdf, x1, y1, x2, y2);
		current = current->next;
	}
}

//#####  MAIN fdf  #####

int		main(int argc, char **argv)
{
	t_env   fdf;
	t_map   *map;
	int     i;
	int     fd;

	if (argc != 2)
	{
		ft_putendl("error");
		return (-1);
	}
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
		printf("%d", map->p_alpha->x);
			printf(" ");
		map->p_alpha = (map->p_alpha)->next;
		i++;
	}
	// tools
	fdf.x_start = 50;
	fdf.y_start = 50;
	fdf.x_prev = fdf.x_start;
	fdf.y_prev = fdf.y_start;
	fdf.x_gap = 10;
	fdf.y_gap = 10;
	fdf.width = 1300;
	fdf.height = 800;
	fdf.size_img = fdf.width * fdf.height;
	fdf.mlx_ptr = mlx_init();
	fdf.win_ptr = mlx_new_window(fdf.mlx_ptr, fdf.width, fdf.height, "fdf");
	fdf.img_ptr = mlx_new_image(fdf.mlx_ptr, fdf.width, fdf.height);
	fdf.img_data = (unsigned int *)mlx_get_data_addr(fdf.img_ptr, &fdf.bits_per_pixel, &fdf.size_line , &fdf.endian);
	draw(map->p_alpha, &fdf);
	mlx_put_image_to_window(fdf.mlx_ptr, fdf.win_ptr, fdf.img_ptr, 0 ,0);
	//printf("HERE\n");
	close(fd);
	//printf("HERE\n");
	mlx_loop(fdf.mlx_ptr);
	//printf("HERE\n");
	return (0);
}
