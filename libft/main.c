#include "libft.h"

int main(int argc, char **argv)
{
	if (argc != 2)
		return (0);
	char **map;
	int i;

	i = 0;
	map = ft_strsplit(argv[1], ',');
	while (map[i])
	{
		ft_putstr(map[i]);
		i++;
	}
	return (0);
}
