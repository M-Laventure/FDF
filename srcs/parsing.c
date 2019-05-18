/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malavent <malavent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 15:11:49 by brobson           #+#    #+#             */
/*   Updated: 2019/05/18 18:34:36 by brobson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/fdf.h"

static int	parsing_precoma(char *precoma)
{
	int i;

	i = 0;
	while (precoma[i])
	{
		if (ft_isdigit(ft_atoi(precoma + i) == 0))
			exit(-1);
		i++;
	}
	return (1);
}

static int	parsing_postcoma(char *post_coma)
{
	while (*post_coma)
	{
		if (!ft_is_inbase(16, *post_coma))
			exit(-1);
		post_coma++;
	}
	return (1);
}

static int	check_ifvalid(char *line)
{
	int i;

	i = -1;
	while (line[++i])
	{
		if (!(ft_strchr(VALID, line[i])))
		{
			ft_putendl_fd(INVALID, 2);
			exit(-1);
		}
	}
	return (1);
}

static void	put_endl_exit(void)
{
	ft_putendl("invalid map");
	exit(-1);
}

int			parsing(char *line)
{
	char	*post_c;
	int		len;
	int		i;

	len = 0;
	i = 0;
	check_ifvalid(line);
	if (ft_strchr(line, ',') != NULL)
	{
		if (!(post_c = ft_strdup(ft_strchr(line, ',') + 3)))
			put_endl_exit();
		while (line[i++] != ',')
			len++;
		i = 0;
		parsing_postcoma(post_c);
		if (line[len] != ',' || (line[len + 1] != '0' && line[len + 2] != 'x'))
			put_endl_exit();
		ft_strdel(&post_c);
	}
	else
		parsing_precoma(line);
	return (1);
}
