#include "../Includes/fdf.h"
#include <stdio.h>

int ft_strlen_tab(char **tab)
{
	int i;

	i = 0;
	while (tab[i] != 0)
		i++;
	return (i);
}

int  ft_nblines(int fd)
{
	int nb_lines;
	int r;
	char *line;

	nb_lines = 0;
	while ((r = ft_get_next_line(fd, &line)) > 0)
		nb_lines++;
	return (nb_lines);
}

void ft_tabdel(char **tab)
{
	if (!tab)
		return ;
	while (*tab)
	{
		free(*tab);
		tab++;
	}
	free(tab);
	tab = NULL;
}

void ft_pxl_pushback(t_pixel **begin, t_pixel *maillon)
{
	t_pixel *tmp;
	tmp = *begin;
	
	if (tmp == 0)
		tmp = maillon;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = maillon;
	}
	maillon->next = NULL;
}	

t_map *ft_init_map(int fd)
{
	t_map *map;
	t_pixel *p_alpha;
	char *line;
	char **tmp_line;

	line = 0;
	ft_get_next_line(fd, &line);
	tmp_line = ft_strsplit(line, ' ');
	if (!(map = (t_map *)malloc(sizeof(t_map))) || !(p_alpha = ft_memalloc(sizeof(p_alpha))))
		return (NULL);
	map->nb_lines = ft_nblines(fd);
	map->nb_col =  ft_strlen_tab(tmp_line);
	map->map_size = map->nb_lines * map->nb_col;
	map->p_alpha = p_alpha;
	ft_strdel(&line);
//	ft_tabdel(tmp_line);
	return (map);
}

int ft_parsing(char *line)
{
	char *post_coma;

	if (ft_strchr(line, ',') != NULL)
	{
		if (!(post_coma = ft_strdup(ft_strchr(line, ',') + 3))) //parsing of color after prefix  "0x"
			return (-1);
	}                       
	if (ft_strchr(line, ',') == NULL)
		return (ft_isdigit(*line) && (ft_strlen(line) == 1) ? 1 : 0);
	else
	{
		if (!ft_isdigit(*line) || line[1] != ',' || (line[2] != '0' && line[3] != line[3]))
			return (-1);	
		while (*post_coma)
		{
			if (!ft_is_inbase(16, *post_coma))
				return (-1);
			post_coma++;
		}
	}
	return (1);
}

int main(int argc, char **argv)
{
	t_map *map;
	int fd;

	if (argc != 2)
		return (0);
	fd = open(argv[1], O_RDONLY);
	map = ft_get_map(fd);
	printf("Nb_lines : %d\n", map->nb_lines);
/*	while (map->p_alpha)
	{
		//printf("HERE\n");
		printf("%d\n", map->p_alpha->z);
		map->p_alpha = map->p_alpha->next;
	}*/	
	return (0);
}
