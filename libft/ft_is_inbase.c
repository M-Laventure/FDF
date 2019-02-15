/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_inbase.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malavent <malavent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 10:11:00 by malavent          #+#    #+#             */
/*   Updated: 2019/02/14 12:21:54 by malavent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_is_inbase(int base_src, char c)
{
	if (base_src <= 10)
		return (c >= '0' && c < '0' + base_src);
	else
	{
		if (c >= '0' && c <= '9')
			return (1);
		return ((c >= 'A' && c < 'A' + (base_src % 10))
		|| (c >= 'a' && c < 'a' + (base_src % 10)));
	}
}