/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brobson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 14:42:19 by brobson           #+#    #+#             */
/*   Updated: 2019/05/06 16:46:58 by brobson          ###   ########.fr       */
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
		nb_lines++;
	return (nb_lines);
}

t_pixel	*ft_init_pix(void)
{
	t_pixel *new;

	if (!(new = (t_pixel *)malloc(sizeof(t_pixel))))
		return (NULL);
	ft_bzero(new, sizeof(t_pixel));
	new->next = NULL;
	return (new);
}
