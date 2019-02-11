#include "../Includes/fdf.h"

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

int ft_strlen_tab(char **tab)
{
    int i;

    i = 0;
    while (tab[i] != 0)
        i++;
    return (i);
}

t_pixel *ft_get_pixel(char *str)
{
    t_pixel *pixel;

    if (!(ft_strchr((const char *)str)))
        ft_fill_pixel()
    if (!(color = ft_strsub((const char *)str_pix, 0, i - 1)))
        return (NULL);
    if (!(alt = ft_strsub(const char *)pixel i + 1, str_len - (i - 1)))
        return (NULL);
    pixel->color = ft_atoi_base(color, 10);
    pixel->alt = ft_atoi_base(alt, 10);
    return (pixel);
}

t_pixel *ft_getline(char *line)
{
    t_pixel *pixel_line;
    char **res;
    int r;
    size_t line_size;
    int i;
    
    i = 0;
    if (!(res = ft_strsplit(line, ',')))
        return (NULL);
    line_size = ft_strlen_tab(res);
    if (!(pixel_line = (t_pixel *)malloc(sizeof(t_pixel) * line_size + 1)))
        return (NULL);
    pixel_line[line_size] = NULL;
    while (pixel_line[i])
    {
        if (!(pixel_line[i] = ft_getpixel(res[i], &)));
        {
            free(pixel_line);
            return (NULL);
        }
        i++;
    }
    ft_tabdel(res);
    return (pixel_line);
}
//Récupere la liste map


t_map *get_map(int fd, char **)
{
    t_map *map;
    t_map *tmp;
    char *ret_gnl;
    char **tmp_line
    int i;
    int r; 

    i = 0;
    if (!(map = ft_init(fd)))
        return (NULL);
    while ((r = ft_get_next_line(fd, &ret_gnl) > 0))
    {
        if (!(tmp_line) = ft_strsplit(ret_gnl, ' '))
            return (NULL);
        while (tmp_line[i])
        {

        }
    }
    }
}
