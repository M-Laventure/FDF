#include "../Includes/fdf.h"

void    fill_pxl(t_env *fdf, int x, int y, int color)
{
    fdf->img_data[y * fdf->width + x] = color;
}