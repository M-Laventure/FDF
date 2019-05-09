/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malavent <malavent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 15:11:49 by brobson           #+#    #+#             */
/*   Updated: 2019/05/09 09:26:09 by malavent         ###   ########.fr       */
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
		{
		//	ft_strdel(&precoma);
			exit(-1);
		}
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

int			ft_parsing(char *line)
{
	char	*post_c;
	int		len;
	int		i;

	len = 0;
	i = 0;
	if (ft_strchr(line, ',') != NULL)
	{
		if (!(post_c = ft_strdup(ft_strchr(line, ',') + 3)))
			exit(-1);
		while (line[i++] != ',')
			len++;
		i = 0;
		if (!(parsing_postcoma(post_c)))
			exit(-1);
		if (line[len] != ',' || (line[len + 1] != '0' && line[len + 2] != 'x'))
			exit(-1);
		ft_strdel(&post_c);
	}
	else
	{
		if (!parsing_precoma(line))
			exit(-1);
	}
	return (1);
}
