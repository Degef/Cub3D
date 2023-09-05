#include "../includes/cub3D.h"

void	free_double_array(char ***str)
{
	int	i;

	i = -1;
	while ((*str)[++i])
		free((*str)[i]);
	free(*str);
}

void	free_double_array2(unsigned int ***str)
{
	int	i;

	i = -1;
	while ((*str)[++i])
		free((*str)[i]);
	free(*str);
}
