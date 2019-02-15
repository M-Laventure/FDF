/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_itoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malavent <malavent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 10:06:50 by malavent          #+#    #+#             */
/*   Updated: 2018/11/23 10:25:47 by malavent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	ft_convert_itoc(int value)
{
	char	*base_ref;

	base_ref = "0123456789abcdef";
	return (base_ref[value]);
}
