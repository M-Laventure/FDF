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

t_pixel *ft_init_pix(void)
{
	t_pixel *new;

	if (!(new = (t_pixel *)malloc(sizeof(t_pixel))))
		return (NULL);
	ft_bzero(new, sizeof(t_pixel));
	new->next = NULL;
	return (new);
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

void ft_pxl_pushback(t_pixel *begin, t_pixel *node)
{	
	if (begin->next == NULL)
		begin->next = node;
	else
		ft_pxl_pushback(begin->next, node);	
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
	if (!(map = (t_map *)malloc(sizeof(t_map))) || !(p_alpha = ft_init_pix()))
		return (NULL);
	map->nb_lines = ft_nblines(fd);
	map->nb_col =  ft_strlen_tab(tmp_line);
	map->map_size = map->nb_lines * map->nb_col;
	map->p_alpha = p_alpha;
	map->p_alpha->next = NULL;
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
		if (!ft_isdigit(*line) || line[1] != ',' || (line[2] != '0' && line[3] != 'x'))
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
	int i;

	i = 0;
	if (argc != 2)
		return (0);
	fd = open(argv[1], O_RDONLY);
	printf("HERE\n");
	map = ft_get_map(fd);
	printf("Nb_lines : %d\n", map->nb_lines);
	printf("HERE\n");
	while (map->p_alpha)
	{
		if (i % (map->nb_col) == 0 && i != 0)
			printf("\n");
		printf("%d", map->p_alpha->z);
		printf(",%u", map->p_alpha->color);
		if (map->p_alpha->next && map->p_alpha->next->z == 50)
			printf(" ");
		else if (map->p_alpha->next && (map->p_alpha->z == 0 || map->p_alpha->z == 50) && (map->p_alpha->next->z == 0))
			printf("  ");
		map->p_alpha = (map->p_alpha)->next;
		i++;
	}
	return (0);
}
