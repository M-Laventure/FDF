/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brobson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 15:40:21 by brobson           #+#    #+#             */
/*   Updated: 2019/04/08 16:36:26 by malavent         ###   ########.fr       */
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

void	get_under_node(t_env *fdf, t_map *map, t_pixel *current)
{
	static int i = 1;

	printf("i = %d\n", i);
	if ((i % (map->nb_col + 1) == 0) && current)
	{
		fdf->x2 = current->x;
		fdf->y2 = current->y;
		fdf->z2 = current->z;
		i = 1;
		return ;
	}
	if (!current)
		return ;
	printf("i = %d\n", i);
	i++;
	get_under_node(fdf, map, current->next);
}

void	set_down(t_map *map, t_env *fdf, t_pixel *current)//, void (*set_coord[2])(t_env *))
{
	printf("currentY%d\n", current->y);
	fdf->x1 = current->x;
	fdf->y1 = current->y;
	fdf->z1 = current->z;
	get_under_node(fdf, map, current);
	printf("underY%d\n", fdf->y2);

	/*printf("-------Down------------\n");
	printf("X1:%d\n", fdf->x1);
	printf("X2:%d\n", fdf->x2);
	printf("Y1:%d\n", fdf->y1);
	printf("Y2:%d\n", fdf->y2);*/

//	set_coord[fdf->proj_type](fdf);
	segment(fdf, current->color);
}

void	set_right(t_env *fdf, t_pixel *current)//, void (*set_coord[2])(t_env *))
{
	fdf->x1 = current->x;
	fdf->y1 = current->y;
	fdf->x2 = (current->next)->x;
	fdf->y2 = (current->next)->y;
	fdf->z1 = current->z;
	fdf->z2 = (current->next)->z;
//	set_coord[fdf->proj_type](fdf);
	segment(fdf, current->color);
}

void	set_coord_para(t_env *fdf)
{
	printf("ONESTLAPROJPARA\n");
	fdf->x1 = fdf->x1 + (CTE1 * fdf->z1);
	fdf->y1 = fdf->y1 + ((CTE1 / 2) * fdf->z1);
	fdf->x2 = fdf->x2 + ((CTE1 * fdf->z2));
	fdf->y2 = fdf->y2 + ((CTE1 / 2) * fdf->z2);
}

void	set_coord_iso(t_env *fdf)
{
	printf("ONESTLAPROJISO\n");
	int stock1;
	int stock2;

	stock1 = fdf->x1;
	stock2 = fdf->x2;
	fdf->x1 = (CTE1 * (fdf->x1)) - (CTE2 * (fdf->y1));
	fdf->y1 = fdf->z1 + ((CTE1 / 2) * stock1) + ((CTE2 / 2) * (fdf->y1));
	fdf->x2 = (CTE1 * (fdf->x2)) - (CTE2 * (fdf->y2));
	fdf->y2 = fdf->z2 + ((CTE1 / 2) * stock2) + ((CTE2 / 2) * (fdf->y2));
}

void	draw(t_pixel *current, t_map *map, t_env *fdf)
{
	int j;
	int i;

	i = 1;
	j = 1;
//	void (*set_coord[2])(t_env *) = {set_coord_iso, set_coord_para};
	while (current)
	{
		if ((i % map->nb_col == 0))
		{
			printf("Jdown = %d\n", j);
			set_down(map, fdf, current);//, set_coord);
			j++;
		}
		else if (j % map->nb_lines == 0)
		{
			printf("Jright = %d\n", j);
			set_right(fdf, current);//, set_coord);
		}
		else
		{
			printf("Jgen = %d\n", j);
			set_right(fdf, current);//, set_coord);
			set_down(map, fdf, current);//,set_coord);
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
	// tools
	fdf.x_start = 200;
	fdf.y_start = 200;
	fdf.x_gap = 50;
	fdf.y_gap = 80;
	fdf.width = 2160;
	fdf.height = 1440;
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
	map = ft_get_map(fd, &fdf);
/*	while (map->p_alpha)
	{
	  if (i % (map->nb_col) == 0 && i != 0)
	  printf("\n");
	  printf("%d", map->p_alpha->y);
	  printf(" ");
	  map->p_alpha = (map->p_alpha)->next;
	  i++;
	}*/
	printf("HERE\n");
	draw(map->p_alpha, map, &fdf);
	mlx_put_image_to_window(fdf.mlx_ptr, fdf.win_ptr, fdf.img_ptr, 0 ,0);
	close(fd);
	mlx_loop(fdf.mlx_ptr);
	//printf("HERE\n");
	return (0);
}
