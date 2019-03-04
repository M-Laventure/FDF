#include "../Includes/fdf.h"

t_pixel *ft_get_line(int y, char *ret_gnl)
{
		t_pixel *tmp;
		t_pixel *begin;
		char 	**tmp_line;
		int x;

		x = -1;
				tmp = ft_memalloc(sizeof(t_list *));
		begin = tmp;
		if (!(tmp_line = ft_strsplit(ret_gnl, ' ')))
				return (NULL);
		while (tmp_line[++x])
		{
			
		//		printf("H get line 1\n");	
				if (ft_parsing(tmp_line[x]) == -1)
						return (NULL);
		//		printf("H get line 2\n");	
				if (!(tmp = ft_get_pixel(tmp_line[x], x, y)))
						return (NULL);
				printf("H get line 3\n");	
				tmp = tmp->next;
		}
		printf("%d\n", begin->z);
		//ft_tabdel(tmp_line);
		printf("HERE\n");
		return (begin);
}

t_pixel *ft_get_pixel(char *str, int x, int y)
{
		t_pixel *pixel;
		char    *tmp;
		char    *post_coma;
		
		post_coma = NULL;
		if (ft_strchr(str, ',') != NULL)
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

t_map *ft_get_map(int fd)
{
		t_map   *map;
		t_pixel *pix_line;
		char    *ret_gnl;
		int     y;

		y  = 0;
		ft_get_next_line(fd, &ret_gnl);
		if (!(map = ft_init_map(fd)))
				return (NULL);	
		lseek(fd, 0, SEEK_SET);
		while ((ft_get_next_line(fd, &ret_gnl) > 0))
		{
				printf("H get map 1\n");	
				pix_line = ft_get_line(y, ret_gnl);
				printf("%d\n", map->nb_col);		
				printf("H get map 2\n");	
				printf("%d\n", pix_line->z);
				if (map->nb_col != ft_strlen(ret_gnl))
						return (NULL);  
				printf("HERE\n");
				if (!(pix_line = ft_get_line(y, ret_gnl)))
						return (NULL);
				ft_pxl_pushback(&map->p_alpha, pix_line);
				
				y++;
		}
		printf("HERE\n");
	/*	while (map->p_alpha)
		{
				//printf("HERE\n");
				printf("%d\n", map->p_alpha->z);
				map->p_alpha = map->p_alpha->next;
    	}*/
		return (map);
}
