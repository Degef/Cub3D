#ifndef CUB3D_H
#define CUB3D_H

#include <stdio.h>
#include "../libft/libft.h"
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <ctype.h>
# include <unistd.h>
# include <limits.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include "../mlx/mlx.h"

typedef struct	s_parse
{
	char	**map;
	int		num_lines;
	char	**text;
	// int		error;
	// int		rx;
	// int		ry;
	char	*no_text;
	char	*so_text;
	char	*we_text;
	char	*ea_text;
	char	*sprite_text;
	int		floor[3];
	int		ceil[3];
	int		map_size;
	char	player_or;
	int		nbr_str;
}				t_parse;

typedef struct	s_data
{
	t_parse		parse;
}				t_data;

void	free_double_array(char ***str, int len);
void	print_double_array(char **str);
int 	read_map(t_parse *parse, const char* file_name);
int 	parse_map(t_parse *parse);

#endif