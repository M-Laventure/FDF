/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malavent <malavent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 12:32:48 by malavent          #+#    #+#             */
/*   Updated: 2018/11/26 11:36:22 by malavent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_sign(int n)
{
	if (n < 0)
		return (1);
	return (0);
}

static int	ft_intmin(int *n)
{
	if (*n == -2147483648)
	{
		*n = -147483648;
		return (1);
	}
	return (0);
}

char		*ft_itoa(int n)
{
	int		negative;
	int		size;
	char	*itoa;
	int		intmin;

	size = 0;
	negative = ft_sign(n);
	intmin = ft_intmin(&n);
	n = (negative == 1) ? -n : n;
	size += ft_intsize(n) + negative + intmin;
	if (!(itoa = (char *)ft_memalloc(sizeof(char) * (size + 1))))
		return (NULL);
	itoa[size] = '\0';
	if (negative)
	{
		if (intmin)
			itoa[1] = 50;
		itoa[0] = '-';
	}
	while (--size >= (negative + intmin))
	{
		itoa[size] = (n % 10) + 48;
		n = (n / 10);
	}
	return (itoa);
}
