#include "../includes/cub3D.h"

void	free_double_array(char ***str, int len)
{
	int	i;

	i = -1;
	while (++i < len)
		free((*str)[i]);
	free(*str);
}

