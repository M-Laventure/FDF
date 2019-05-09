/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malavent <malavent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 14:42:19 by brobson           #+#    #+#             */
/*   Updated: 2019/05/09 13:43:44 by malavent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/fdf.h"

void	put_menu(t_env *fdf)
{
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 0, 0, 0xffd700, ARROWS);
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 0, 20, 0xffd700, ZOOM);
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 0, 40, 0xffd700, SWITCH);
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 0, 60, 0xffd700, COLORS);
	mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, 0, 80, 0xffd700, Z);
}

void	free_pix(t_pixel *pixel)
{
	if (!pixel)
		return ;
	t_pixel *tmp;

	while (pixel->next)
	{
		tmp = pixel;
		pixel = pixel->next;
		free(tmp);
	}
	free(pixel);
	pixel = NULL;
	tmp = NULL;
	//ft_memdel((void **)&pixel->next);
	//ft_memdel((void **)pixel);
}
void	clear_window(t_env *fdf, int mod)
{
	mlx_clear_window(fdf->mlx_ptr, fdf->win_ptr);
	empty_tab(fdf);
	if (mod == 1)
		mlx_destroy_window(fdf->mlx_ptr, fdf->win_ptr);
}

int		ft_strlen_tab(char **tab)
{
	int i;

	i = 0;
	while (tab[i] != 0)
		i++;
	return (i);
}

int		ft_nblines(int fd)
{
	int		nb_lines;
	int		r;
	char	*line;

	nb_lines = 0;
	while ((r = ft_get_next_line(fd, &line)) > 0)
	{
		nb_lines++;
		ft_strdel(&line);
	}
	return (nb_lines);
}

t_pixel	*ft_init_pix(void)
{
	t_pixel *new;

	if (!(new = (t_pixel *)malloc(sizeof(t_pixel))))
		exit(-1);
	ft_bzero(new, sizeof(t_pixel));
	new->next = NULL;
	return (new);
}

void	free_env(t_env *fdf)
{
	ft_memdel((void **)&fdf->map);
	ft_memdel((void **)&fdf->add_color);
	ft_memdel((void **)&fdf->img_data);
	ft_memdel((void **)&fdf->arg);
	ft_memdel((void **)&fdf);
}

