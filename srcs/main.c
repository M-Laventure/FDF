/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brobson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 15:40:21 by brobson           #+#    #+#             */
/*   Updated: 2019/03/21 16:02:07 by malavent         ###   ########.fr       */
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

void	set_coord_para(int *x1, int *y1, int *x2, int *y2, int z)
{
	*x1 =  *x1 + (CTE1(z) * z);
	*y1 = *y1 + ((CTE1(z) / 2) * z);
	*x2 = *x2 + ((CTE1(z) * z));
	*y2 = *y2 + ((CTE1(z) / 2) * z);
}

void	set_coord_iso(int *x1, int *y1, int *x2, int *y2, int z)
{
	int stock1;
	int stock2;

	stock1 = *x1;
	stock2 = *x2;
	*x1 = (CTE1(z) * (*x1)) - (CTE2(z) * (*y1));
	*y1 = z + ((CTE1(z) / 2) * stock1) + ((CTE2(z) / 2) * (*y1));
	*x2 = (CTE1(z) * (*x2)) - (CTE2(z) * (*y2));
	*y2 = z + ((CTE1(z) / 2) * stock2) + ((CTE2(z) / 2) * (*y2));
}

void	draw(t_pixel *current, t_map *map, t_env *fdf)
{
	int i;
	int	j;
	int x1; 
	int y1;
	int x2;
	int y2;
	int color;
	i = 1;
	j = 1;

	while (current->next)
	{
		printf("current x : %d\n", current->x);
		color  = current->color;
		if ((i % map->nb_col == 0))
		{
			j++;
			x1 = current->x;
			y1 = current->y;
			x2 = current->x;
			y2 = current->y + fdf->y_gap;
			set_coord[fdf->proj_type](&x1, &x2, &y1, &y2, current->z);
			segment(fdf, x1, y1, x2, y2, color);
		}
		else if (j % map->nb_lines == 0)
		{
			x1 = current->x;
			y1 = current->y;
			x2 = current->x + current->next->x;
			y2 = current->y;
			set_coord[fdf->proj_type](&x1, &x2, &y1, &y2, current->z);
			segment(fdf, x1, y1, x2, y2, color);
		}
		else
		{
			x1 = current->x;
			y1 = current->y;
			x2 = current->x;
			y2 = current->y + fdf->y_gap;
			set_coord[fdf->proj_type](&x1, &x2, &y1, &y2, current->z);
			segment(fdf, x1, y1, x2, y2, color);
			//
			x1 = current->x;
			y1 = current->y;
			x2 = current->x + current->next->x;
			y2 = current->y;
			set_coord[fdf->proj_type](&x1, &x2, &y1, &y2, current->z);
			segment(fdf, x1, y1, x2, y2, color);
		}
		current = current->next;
		i++;
	}
}

//#####  MAIN fdf-> #####

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
	// tools 
	i = 0;
	/*while (map->p_alpha)
	  {
	  if (i % (map->nb_col) == 0 && i != 0)
	  printf("\n");
	  printf("%d", map->p_alpha->x);
	  printf(" ");
	  map->p_alpha = (map->p_alpha)->next;
	  i++;
	  }*/
	// tools
	fdf.x_start = 200;
	fdf.y_start = 200;
	fdf.x_prev = fdf.x_start;
	fdf.y_prev = fdf.y_start;
	fdf.x_gap = 50;
	fdf.y_gap = 80;
	fdf.width = 2160;
	fdf.height = 1440;
	fdf.size_img = fdf.width * fdf.height;
	fdf.mlx_ptr = mlx_init();
	fdf.win_ptr = mlx_new_window(fdf.mlx_ptr, fdf.width, fdf.height, "fdf");
	fdf.img_ptr = mlx_new_image(fdf.mlx_ptr, fdf.width, fdf.height);
	fdf.img_data = (unsigned int *)mlx_get_data_addr(fdf.img_ptr, &fdf.bits_per_pixel, &fdf.size_line , &fdf.endian);
	map = ft_get_map(fd, &fdf);
	printf("HERE\n");
	draw(map->p_alpha, map, &fdf);
	printf("HERE\n");
	mlx_put_image_to_window(fdf.mlx_ptr, fdf.win_ptr, fdf.img_ptr, 0 ,0);
	close(fd);
	mlx_loop(fdf.mlx_ptr);
	//printf("HERE\n");
	return (0);
}
