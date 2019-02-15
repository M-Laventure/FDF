/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malavent <malavent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 13:39:26 by malargve          #+#    #+#             */
/*   Updated: 2019/01/31 16:47:36 by malavent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strjoin_free(char **s1, char **s2)
{
	char	*str;
	size_t	size;

	if (!s1 || !s2)
		return (NULL);
	size = ft_strlen(*s1) + ft_strlen(*s2);
	if (!(str = (char*)malloc(sizeof(char) * size + 1)))
		return (NULL);
	ft_strcpy(str, *s1);
	ft_strcat(str, *s2);
	ft_strdel(s1);
	ft_strdel(s2);
	return (str);
}

static	int		ft_strxlen(char *str, int x)
{
	int n;

	n = 0;
	while (str[n] != '\0' && str[n] != x)
		n++;
	return (n);
}

static int		read_ret(const int fd, char **fd_rets)
{
	char	buff[BUFF_SIZE + 1];
	char	*temp;
	char	*tmp;
	int		r_bytes;

	temp = NULL;
	while ((r_bytes = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[r_bytes] = '\0';
		if (!fd_rets[fd])
		{
			if (!(fd_rets[fd] = ft_strdup(buff)))
				return (-1);
		}
		else
		{
			tmp = ft_strdup(buff);
			if (!(temp = ft_strjoin_free(&(fd_rets[fd]), &tmp)))
				return (-1);
			fd_rets[fd] = temp;
		}
		if (ft_strchr(fd_rets[fd], '\n') != NULL)
			return (r_bytes);
	}
	return (r_bytes);
}

static	char	*move_head(char *fd_rets, int head)
{
	char *temp;

	temp = NULL;
	if (fd_rets[head] == '\n')
	{
		if (!(temp = ft_strdup(fd_rets + head + 1)))
			return (NULL);
	}
	else if (fd_rets[head] == '\0')
	{
		if (!(temp = ft_strnew(0)))
			return (NULL);
	}
	ft_strdel(&fd_rets);
	fd_rets = temp;
	return (fd_rets);
}

int				ft_get_next_line(const int fd, char **line)
{
	static	char	*fd_rets[10240];
	int				r_bytes;
	int				head;

	head = 0;
	if (fd < 0 || !line)
		return (-1);
	if ((r_bytes = read_ret(fd, fd_rets)) < 0)
		return (-1);
	if (r_bytes == 0 && fd_rets[fd] == NULL)
		return (0);
	else if (r_bytes == 0 && *fd_rets[fd] == '\0')
	{
		free(fd_rets[fd]);
		fd_rets[fd] = NULL;
		return (0);
	}
	head = ft_strxlen(fd_rets[fd], '\n');
	if (!(*line = ft_strsub(fd_rets[fd], 0, head)))
		return (-1);
	if (!(fd_rets[fd] = move_head(fd_rets[fd], head)))
		return (-1);
	return (1);
}
