#include "../Includes/fdf.h"

t_pixel *ft_get_line(int y, t_pixel *pix_line, char *ret_gnl)
{
    t_pixel *tmp;
    char **tmp_line;
    int x;

    x = 0;
    tmp = pix_line;
    if (!(tmp_line = ft_strsplit(ret_gnl, ' ')))
        return (NULL);
    while (tmp_line[++x])
    {
        if (ft_parsing(tmp_line[x]) == -1)
            return (NULL);
        if (!(tmp = ft_get_pixel(tmp_line[x], x, y)))
            return (NULL);
        tmp->next = ft_memalloc(sizeof(t_pixel *));
    }
    ft_tabdel(tmp_line);
    return (pix_line);
}

t_pixel *ft_get_pixel(char *str, int x, int y)
{
    t_pixel *pixel;
    char    *tmp;
    char    *post_coma;

    post_coma = ft_strdup(ft_strchr((char const *)str, ',') + 1);
    if (!(pixel = ft_memalloc(sizeof(t_pixel *))))
        return (NULL);
    if (post_coma != NULL)
    {
        if (!(tmp = ft_strsub(str, 0, ft_strnlen(str, ','))))
            return (NULL);
        pixel->z = ft_atoi(tmp);
        ft_strdel(&tmp);
        pixel->color = ft_atoi_base(post_coma, 16, 10);
    }
    else
    {
        pixel->z = ft_atoi(str);
        pixel->color = 16777215;
    }
    pixel->x = x;
    pixel->y = y;
    return (pixel);
}

t_map ft_get_map(int fd)
{
    t_map   *map;
    t_pixel *pix_line;
    t_pixel *begin_map;
    char    *ret_gnl;
    int     y;

    y  = 0;
    if (!(map = ft_init_map(fd)) || (!(begin_map = ft_memalloc(sizeof(*t_pixel)))))
        return ();
    tmp_pix = begin_map;
    map->p_alpha = begin_map;
    while ((ft_get_next_line(fd, &ret_gnl) > 0))
    {
        printf("%s\n", ret_gnl);
        if (map->nb_col != ft_strlen(ret_gnl))
            return (NULL);  
        if (!(tmp_pix = ft_get_line(int y, pix_line, ret_gnl)))
            return (NULL);
        y++;
    }
    return (map);
}
