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
# include "../mlx_linux/mlx.h"

typedef struct ray
{
	double		a;
	int			num;
	t_coord		ray;
	t_coord		offset;
	double		_tan;
	t_coord		h_fcord;
	t_coord		v_fcord;
	double		h_fdis;
	double		v_fdis;
	t_cub_main	*main;
	int			check_num;
	t_coord		wc_temp;
	double		f_dis;
	double		h_line;
	double		h_offset;
	int			dir;
	double		draw_end;
	double		draw_start;
}	t_ray;

typedef struct s_pos
{
	double	x;
	double	y;
}	t_pos;

typedef struct mlx
{
	void	*window;
	void	*mlx;
	void	*width;
	void	*height;
}	t_mlx;

typedef struct	s_parse
{
	char	**map;
	int		num_lines;
	char	**text;
	char	*no_text;
	char	*so_text;
	char	*we_text;
	char	*ea_text;
	int		floor[3]; //colors are in RBG (red, blue, green)
	int		ceil[3]; //colors are in RBG (red, blue, green)
	int		map_size;
	size_t		column;
	size_t		row;
	char	player_or;
	int		nbr_str;
}				t_parse;

typedef struct	s_data
{
	t_parse		*parse;
	t_mlx		mlx;
	t_pos		pos;
}				t_data;

void	free_double_array(char ***str);
void	print_double_array(char **str);
int 	read_map(t_parse *parse, const char* file_name);
int 	parse_map(t_parse *parse);
int 	map_valid(char **map, t_parse *parse);
int 	start_game(t_data *data);
void 	free_memory(t_parse *parse);

#endif
