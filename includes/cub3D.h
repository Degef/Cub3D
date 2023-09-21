/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Degef <dsium@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 18:14:54 by Degef             #+#    #+#             */
/*   Updated: 2023/09/21 19:16:05 by Degef            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include "../libft/libft.h"
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

# define X_EVENT_KEY_PRESS		2
# define X_EVENT_KEY_RELEASE	3
# define X_EVENT_EXIT			17

# define WIN_W	720
# define WIN_H	520
# define STEP_SIZE  30.00
# define FOV 60.00
# define ROTATION_ANGLE 0.19
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

typedef struct s_parse
{
	char	**map;
	int		num_lines;
	char	**text;
	char	*no_text;
	char	*so_text;
	char	*we_text;
	char	*ea_text;
	int		floor_color;
	int		ceil_color;
	int		map_size;
	size_t	column;
	size_t	row;
	char	player_or;
	int		nbr_str;
}				t_parse;

typedef struct s_ray {
	double			angle;
	struct s_data	*data;
	double			x;
	double			y;
	double			x_intercept;
	double			y_intercept;
	int				h_wall_hit_flag;
	int				v_wall_hit_flag;
	double			h_distance;
	double			v_distance;
	double			ray_length;
	double			wall_height;
	int				draw_start;
	int				draw_end;
}	t_ray;

typedef struct s_img
{
	void	*background_img;
	void	*wall_img;
	void	*img;
	int		*addr;
	int		bpp;
	int		line_length;
	int		endian;
	int		t_width;
	int		t_height;
}	t_img;

typedef struct s_player
{
	double		x_pos;
	double		y_pos;
	double		angle;
	double		fov;
	double		delta_x;
	double		delta_y;
}	t_player;

typedef struct s_window
{
	void	*mlx;
	void	*win;
	int		map_width;
	int		map_height;
}	t_window;

typedef struct s_keys {
	int		w;
	int		a;
	int		s;
	int		d;
	int		left;
	int		right;
}	t_keys;

typedef struct s_image {
	void	*img;
	int		*addr;
	int		bpp;
	int		line_length;
	int		endian;
}	t_image;

typedef struct s_data
{
	t_parse			*parse;
	t_ray			ray;
	t_player		player;
	t_window		window;
	t_keys			keys;
	double			angle_increment;
	t_image			image;
	t_image			mini_map;
	unsigned int	**buffer;
	int				previous;
	t_img			texture;
	t_img			no_img;
	t_img			so_img;
	t_img			we_img;
	t_img			ea_img;
}				t_data;

//parsing
void	free_double_array(char ***str);
void	free_double_array2(unsigned int ***str);
void	print_double_array(char **str);
int		read_map(t_parse *parse, const char *file_name);
int		parse_map(t_parse *parse);
int		map_valid(char **map, t_parse *parse);
int		start_game(t_data *data);
int		endgame(void *pa);
void	free_memory(t_parse *parse, t_data *data);

//execution
int		start_ray_casting(t_data *data, t_ray *ray);
int		put_pixels(t_data *data);
int		keypress(int key, void *da);
int		key_release(int key_code, void *da);
int		init_buffer(t_data *data);
int		init_attributes(t_data *data);
int		is_wall(t_ray *ray, double x, double y, char **map);
int		pythagoras(t_ray *ray, double x, double y);
int		find_horizontal_intercept(t_ray *ray, char **map);
int		find_vertical_intercept(t_ray *ray, char **map);
int		get_texture(t_parse *parse, t_data *data);
void	draw_mini_map(t_data *data, char **map, int x, int y);
int		fix_fish_eye(t_ray *ray, double player_angle);
int		find_draw_start_end(t_ray *ray, t_data *data, int x);
void	select_ray(t_data *data, t_ray *ray, int x_intercept, int y_intercept);
int		endgame(void *pa);
void	rotate_left(t_data *data);
void	rotate_right(t_data *data);
int		main_loop(void *da);
// void 	draw_player(t_data *data, int x, int y);
// void 	draw_map(t_data *data, char **map, int x, int y);
// void 	draw_rays(t_data *data, int n_rays, int i);
// void		draw_line(t_data *data, int x1, int y1, int x2, int y2, int color);

#endif