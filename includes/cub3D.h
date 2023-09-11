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

# define WIN_W	832
# define WIN_H	640
# define STEP_SIZE  20.00
# define FOV 60.00
# define ROTATION_ANGLE 0.1
# define PI 3.1415926535898
# define CUBE_SIZE 64.00

// keys 
# define ESC 53
# define W 13
# define A 0
# define S 1
# define D 2
# define LEFT 123
# define RIGHT 124


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


typedef struct s_ray {
	double		angle;
	struct s_data 		*data;
	double		x;
	double		y;
	double 		x_intercept;
	double 		y_intercept;
	int 		h_wall_hit_flag;
	int 		v_wall_hit_flag;
	double		h_distance;
	double		v_distance;
	double		ray_length;
}	t_ray;

typedef struct	s_data
{
	t_parse		*parse;
	t_ray 		ray;
	double		x_pos;
	double		y_pos; 
	double		angle;
	double 		fov; 
	double		deltaX;
	double		deltaY;
	void		*window;
	void		*mlx;
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

//parsing
void	free_double_array(char ***str);
void	free_double_array2(unsigned int ***str);
void	print_double_array(char **str);
int 	read_map(t_parse *parse, const char* file_name);
int 	parse_map(t_parse *parse);
int 	map_valid(char **map, t_parse *parse);
int 	start_game(t_data *data);
int 	endgame(void *pa);
void 	free_memory(t_parse *parse, t_data *data);

//execution
int 	start_ray_casting(t_data *data, t_ray *ray);
int 	put_pixels(t_data *data);
int 	move(int key, void *da);
int		init_buffer(t_data *data);
int 	init_attributes(t_data *data);
int 	is_wall(t_ray *ray, double x, double y, char **map);
int 	pythagoras(t_ray *ray, double x, double y);
int 	find_horizontal_intercept(t_ray *ray, char **map);
int 	find_vertical_intercept(t_ray *ray, char **map);
// void 	draw_player(t_data *data, int x, int y);
// void 	draw_map(t_data *data, char **map, int x, int y);
// void 	draw_rays(t_data *data, int n_rays, int i);
// void 	draw_line(t_data *data, int x1, int y1, int x2, int y2, int color);

#endif