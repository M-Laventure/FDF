#include "../Includes/fdf.h"
#include <stdio.h>

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

t_map *ft_init_map(fd)
{
    t_map *map;
    t_pixel *p_alpha;

    if (!(map = (t_map *)malloc(sizeof(t_map))) || !(p_alpha = (t_pixel *)malloc(sizeof(t_pixel))))
        return (NULL);
    map->nb_lines = ft_nblines(fd);
    map->nb_col =  ft_nbcolumns(fd);
    map->map_size = map->nb_lines * map->nb_col;
    ft_bzero(p_alpha, sizeof(*p_alpha));
    map->p_alpha = p_alpha;
    return (map);
}

t_pixel *ft_init_pix()
{   
    t_pixel *pixel

    if (!(pixel = (t_pixel *)malloc(sizeof(t_pixel))))
        return (NULL);
    ft_bzero(pixel, sizeof(t_pixel));
}

int    *ft_fill_pix(t_pixel *pixel, char *str, int i, int y)
{
    if (!(pixel->z) = ft_atoi(str))
        return (0);
    pixel->x = i - 1;
    pixel->y = y;
}

int main(int argc, char **argv)
{
    if (argc != 2)
        return (0);
    printf("%d\n", ft_nbcolumns(open(argv[1], O_RDONLY)));
    printf("%d\n", ft_nblines(open(argv[1], O_RDONLY)));
    return (0);
}