/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brobson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 11:25:40 by brobson           #+#    #+#             */
/*   Updated: 2019/05/06 11:25:42 by brobson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/fdf.h"

int     hexa_pars(char *pre_coma, int *i, char *post_coma, char *line, int len)
{
    while (pre_coma[*i])
	{
		if (ft_isdigit(ft_atoi(&pre_coma[*i++]) == 0))
			return (-1);
	}
	if (line[len] != ',' || (line[len + 1] != '0' && line[len + 2] != 'x'))
		return (-1);
	while (*post_coma)
	{
		if (!ft_is_inbase(16, *post_coma))
			return (-1);
		post_coma++;
	}
    return (1);
}

int     ft_parsing(char *line)
{
	char 	*post_coma;
	char	*pre_coma;
	int		len;
	int		i;

	len = 0;
	i = 0;
	if (ft_strchr(line, ',') != NULL)
	{
		if (!(post_coma = ft_strdup(ft_strchr(line, ',') + 3)))
			return (-1);
		while (line[i++] != ',')
			len++;
		i = 0;
		if (!(pre_coma = ft_strsub(line, 0, len)))
			return (-1);
	}
	if (ft_strchr(line, ',') == NULL)
	{
		while (pre_coma[i])
		{
			if (ft_isdigit(ft_atoi(&pre_coma[i++]) == 0))
				return (-1);
		}
		return (1);
	}
	else
	{
        if (hexa_pars(pre_coma, &i, post_coma, line, len) == -1)
            return (-1);
	}
	return (1);
}