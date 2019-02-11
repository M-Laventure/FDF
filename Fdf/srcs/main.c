#include "../Includes/fdf.h"
#include <stdio.h>

int ft_img_size(int width, int height)
{
    int size;

    size = width * height;
    return (size);
}



//#####  MAIN FDF #####

int main(int argc, char **argv)
{
    t_env fdf;
    int   color;
    int   i;
    int   x;
    int   y;
    int fd;
    char *str_map;
    char **str;
  /*  i = 0;
    x = 0;
    y = 0;
    color = 0xff0000;
    fdf.width = 100;
    fdf.height = 50;
    fdf.size_img = fdf.width * fdf.height;
    fdf.mlx_ptr = mlx_init();
    fdf.win_ptr = mlx_new_window(fdf.mlx_ptr, 2000, 800, "window");
    fdf.img_ptr = mlx_new_image(fdf.mlx_ptr, fdf.width, fdf.height); //width and height img <= windows ?
    fdf.img_data = (unsigned int *)mlx_get_data_addr(fdf.img_ptr, &fdf.bits_per_pixel, &fdf.size_line , &fdf.endian); */
    if ((fd = open(argv[1], O_RDONLY)) == -1)
        return (-1);
    if (!(str_map = ft_strdup(read_map(fd))))
        return (-1);
    //ft_putstr("HERE");
    str = get_map(str_map);
   // ft_putstr("HERE");
    /*while (i < fdf.size_img)
    {
        ft_putnbr(fdf.img_data[i]);
        i++;
    }
  //  mlx_put_image_to_window (fdf.mlx_ptr, fdf.win_ptr, fdf.img_ptr, 0 ,0);
 //   mlx_loop(fdf.mlx_ptr);*/
    return (0);
}
