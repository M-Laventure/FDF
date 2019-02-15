/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malavent <malavent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/18 18:07:34 by malavent          #+#    #+#             */
/*   Updated: 2019/02/14 12:21:52 by malavent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_trim_blanks(const char *str, int *i)
{
	*i = 0;
	while (str[*i] == '\n' || str[*i] == '\v' || str[*i] == '\f'
	|| str[*i] == ' ' || str[*i] == '\r')
		*i += 1;
}

static int	ft_signe(char c)
{
	if (c == '-')
		return (-1);
	return (1);
}


static int ft_atoi_base10_tob(int nb, int base_dest)
{
	int res;
	int stock;
	int quotient;

	res = 0;
	while (nb > base_dest)
	{
		stock = ft_convert_power(nb, base_dest);
		quotient = nb /stock;
		res = res * 10 + quotient;
		nb = nb - (stock * quotient);
	}
	res = res * 10 + nb;
	return (res);
}

int			ft_atoi_base(const char *str, int base_src, int base_dest)
{
	int	i;
	int signe;
	int res;

	signe = 1;
	res = 0;
	if (base_src < 2 || base_src > 16)
		return (0);
	ft_trim_blanks(str, &i);
	if ((str[i] == '-' || str[i] == '+'))
	{
		signe = ft_signe(str[i]);
		if (base_src != 10 && signe == -1)
			return (0);
		i++;
	}
	while (ft_is_inbase(base_src, str[i]))
	{
		res = res * base_src + ft_convert_dec(str[i], base_src);
		i++;
	}
	if (res != 0)
		res = ft_atoi_base10_tob(res, base_dest);
	res = res * signe;
	return (res);
}
