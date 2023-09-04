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

// typedef struct s_pos
// {
// 	double	x;
// 	double	y;
// }	t_pos;

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

typedef struct s_player
{
	double		x_pos;
	double		y_pos; 
	int 		x; 
	int 		y;
	double		angle;
	double 		fov; // should be 60 degrees
	int			height; // should be 32 considering that walls are 64 units high.
}	t_player;


typedef struct s_ray {
	double		angle;
	double		x;
	double		y;
	double		h_x_step;
	double		h_y_step;
	double		v_x_step;
	double		v_y_step;
	double		h_x_intercept;
	double		h_y_intercept;
	double		v_x_intercept;
	double		v_y_intercept;
	double		h_wall_hit_x;
	double		h_wall_hit_y;
	double		v_wall_hit_x;
	double		v_wall_hit_y;
	int 		h_wall_hit;
	int 		v_wall_hit;
	double		x_hit;
	double		y_hit;
	double		h_distance;
	double		v_distance;
	double		distance;
	int			was_hit_vertical;
}	t_ray;

typedef struct	s_data
{
	t_parse		*parse;
	t_mlx		mlx;
	t_ray 		*rays;
	t_player	player;
	int			plane_width; // 320 units wide
	int			plane_height; // 200 units high
	double		plane_dist; // 277.128 units
	double		angle_increment; // 0.1875 degrees
}				t_data;

void	free_double_array(char ***str);
void	print_double_array(char **str);
int 	read_map(t_parse *parse, const char* file_name);
int 	parse_map(t_parse *parse);
int 	map_valid(char **map, t_parse *parse);
int 	start_game(t_data *data);
void 	free_memory(t_parse *parse);

#endif
