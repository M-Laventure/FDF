/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoabase.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malavent <malavent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 11:48:56 by malavent          #+#    #+#             */
/*   Updated: 2019/03/28 14:33:38 by malavent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_fill_itoa(int base, int value, size_t size)
{
	char *itoa;

	if (!(itoa = (char *)ft_memalloc(sizeof(char) * (size + 1))))
		return (NULL);
	itoa[size] = '\0';
	while (value >= base && size)
	{
		itoa[size - 1] = ft_convert_itoc(value % base);
		value = value / base;
		size--;
	}
	itoa[0] = ft_convert_itoc(value);
	return (itoa);
}

char		*ft_itoabase(int value, int base)
{
	char	*itoa;
	size_t	size;

	if (base == 10)
		return (ft_itoa(value));
	value = value < 0 ? -value : value;
	size = ft_numlen_base(value, base);
	itoa = ft_fill_itoa(base, value, size);
	return (itoa);
}
