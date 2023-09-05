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

# define WIN_W	768
# define WIN_H	512
# define STEP_SIZE 10.00
# define FOV 60.00
# define ROTATION_ANGLE 10
# define PI 3.14159265358979323846
# define CUBE_SIZE 64.00

// keys 
# define ESC 53
# define W 13
# define A 0
# define S 1
# define D 2
# define LEFT 123
# define RIGHT 124

typedef struct s_coord
{
	int	x;
	int	y;
}	t_coord;

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
	t_coord		pos;
	t_coord		h_step;
	t_coord		v_step;
	t_coord		h_intercept;
	t_coord		v_intercept;
	t_coord		h_wall_hit;
	t_coord		v_wall_hit;
	t_coord		distance; // x will be distance using horizontal calculations and y will be distance using vertical calculations
	int 		h_wall_hit_flag;
	int 		v_wall_hit_flag;
	// double		h_distance;
	// double		v_distance;
	double		ray_length;
	// int			was_hit_vertical;
}	t_ray;

typedef struct	s_data
{
	t_parse		*parse;
	t_mlx		mlx;
	t_ray 		*rays;
	t_player	player;
	int			plane_width;
	int			plane_height;
	double		plane_dist; 
	double		angle_increment; 
	void		*image;
	int			*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	unsigned int **buffer;
}				t_data;

void	free_double_array(char ***str);
void	free_double_array2(unsigned int ***str);
void	print_double_array(char **str);
int 	read_map(t_parse *parse, const char* file_name);
int 	parse_map(t_parse *parse);
int 	map_valid(char **map, t_parse *parse);
int 	start_game(t_data *data);
int 	endgame(void *pa);
void 	free_memory(t_parse *parse, t_data *data);
int 	move(int key, void *da);
int 	init_attributes(t_data *data);
int 	init_rays(t_data *data);
int 	start_ray_casting(t_data *data);
int		init_buffer(t_data *data);
#endif
