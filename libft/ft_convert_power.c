/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_power.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malavent <malavent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 08:20:10 by malavent          #+#    #+#             */
/*   Updated: 2019/05/06 17:27:53 by brobson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_convert_power(int n, int b)
{
	int i;

	i = 0;
	while (ft_power(b, i) < n)
		i++;
	if (ft_power(b, i) == n)
		return (ft_power(b, i));
	return (ft_power(b, i - 1));
}
