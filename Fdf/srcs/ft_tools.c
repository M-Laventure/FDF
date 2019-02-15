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

t_map *ft_init_map(fd)
{
    t_map *map;
    t_pixel *p_alpha;
    char *line;

    line = 0;
    ft_get_next_line(fd, &line);
    if (!(map = (t_map *)malloc(sizeof(t_map))) || !(p_alpha = ft_init_pix(p_alpha)))
        return (NULL);
    map->nb_lines = ft_nblines(fd);
    map->nb_col =  ft_strlen_tab(line);
    map->map_size = map->nb_lines * map->nb_col;
    map->p_alpha = p_alpha;
    ft_strdel(&line);
    return (map);
}

t_pixel *ft_init_pix()
{   
    t_pixel *pixel;

    if (!(pixel = (t_pixel *)malloc(sizeof(t_pixel))))  
        return (NULL);
    ft_bzero(pixel, sizeof(t_pixel));
    return (pixel);
}

int ft_parsing(char *line)
{
    char *post_coma;

    if (!(post_coma = ft_strdup(ft_strchr(str, ',') + 3))) //parsing of color after prefix  "0x"
        return (-1);                       
    if (ft_strchr(line, ',') == NULL)
        return (ft_is_digit(*line) && (ft_strlen(line) == 1) ? 1 : 0);
    else
    {
        if (!ft_is_digit(*line) || line[1] != ',' || (line[2] != '0' && line[3] != line[3]))
            return (-1);
        while (*post_coma)
        {
            if (!ft_is_inbsase(16, *post_coma))
                return (-1);
            post_coma++;
        }
    }
    return (1);
}

void ft_map_pshback(t_map **map, t_map *pixel)
{
    t_pixel *tmp;

    
    
}

int main(int argc, char **argv)
{

    if (argc != 4)
        return (0);
    printf("%d\n", ft_convert_power(150, 16));
    printf("[%d]\n", ft_atoi_base(argv[1], ft_atoi(argv[2]), ft_atoi(argv[3])));
    return (0);
}