#include "../Includes/fdf.h"

t_pixel *ft_get_pixel(char *str, int x, int y)
{
    t_pixel *pixel;
    char *tmp;
    char *post_coma;

    post_coma = ft_strdup(ft_strchr((char const *)str, ',') + 1);
    if (!(pixel = ft_init_pix))
        return (NULL);
    if (post_coma != NULL)
    {
        if (!(tmp = ft_strsub(str, 0, ft_strnlen(str, ','))))
            return (NULL);
        pixel->z = ft_atoi(tmp);
        free(tmp);
        pixel->color = ft_atoi_base(post_coma);
    }
    else
    {
        pixel->z = ft_atoi(str);
        pixel->color = "OxFFFFFF";
    }
    pixel->x = x;
    pixel->y = y;
    return (pixel);
}

t_map *get_map(int fd)
{
    t_map *map;
    t_pixel *current_pix;
    char *ret_gnl;
    char **tmp_line
    int x;
    int y;
    int r; 

    y  = 0;
    if (!(map = ft_init(fd)))
        return (NULL);
    while ((r = ft_get_next_line(fd, &ret_gnl) > 0))
    {
        i = -1;
        if (map->nb_col != ft_strlen(ret_gnl))
            return (NULL);
        if (!(tmp_line) = ft_strsplit(ret_gnl, ' '))
            return (NULL);
        while (tmp_line[++x])
        {
            if (ft_parsing(tmp_line[x]) == -1)
                return (NULL);
            if (!(current_pix = ft_get_pixel(tmp_line[x], x, y)))
                return (NULL);
            ft_lst_
        }
        y++;
    }
}
