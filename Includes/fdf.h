#ifndef FDF_H
#define FDF_H
#include "mlx.h"
#include "fdf_struct.h"
#include "../libft/libft.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#define RED = 0xff0000

void    fill_pxl(t_env *fdf, int x, int y, int color);
char    *read_map(int fd);
char    **get_map(char *str_map);

#endif