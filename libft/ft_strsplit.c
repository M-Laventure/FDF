/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brobson <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 10:35:43 by brobson           #+#    #+#             */
/*   Updated: 2018/11/16 13:58:14 by brobson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_nbword(const char *s, char c)
{
	size_t		cpt;
	size_t		i;

	cpt = 0;
	i = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i + 1] != '\0')
			i++;
		if ((i >= 1 && s[i] != c && s[i - 1] == c && s[i] != '\0') ||
			(i == 0 && s[i] != c))
			cpt++;
		i++;
	}
	return (cpt);
}

static size_t	ft_lenword(const char *s, char c)
{
	size_t	len;
	int		i;

	i = 0;
	len = 0;
	while (s[i] != c && s[i] != '\0')
	{
		len++;
		i++;
	}
	return (len);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**tab;
	size_t	len;
	size_t	i;

	if (!s)
		return (NULL);
	len = ft_nbword((const char*)s, c);
	i = 0;
	tab = (char**)malloc(sizeof(char*) * (len + 1));
	if (tab == NULL)
		return (NULL);
	while (i < len)
	{
		while (*s == c && *s != '\0')
			s++;
		tab[i] = ft_strsub((const char*)s, 0, ft_lenword((const char*)s, c));
		if (tab[i] == NULL)
			return (NULL);
		s = s + ft_lenword(s, c);
		i++;
	}
	tab[i] = 0;
	return (tab);
}
