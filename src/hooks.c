#include "../includes/cub3D.h"

int endgame(void *pa)
{
	t_data *data;

	data = (t_data *)pa;

	mlx_destroy_window(data->mlx.mlx, data->mlx.window);
	free_memory(data->parse, data);
	exit(0);
}

void move_forward(t_data *data)
{
	double new_x;
	double new_y;

	new_x = data->player.x_pos - cos(data->player.angle * (PI / 180)) * STEP_SIZE;
	new_y = data->player.y_pos - sin(data->player.angle * (PI / 180)) * STEP_SIZE;
	if (data->parse->map[(int)(new_y / 64)][(int)(new_x / 64)] != '1')
	{
		data->player.x_pos = new_x;
		data->player.y_pos = new_y;
	}
}

void move_backward(t_data *data)
{
	double new_x;
	double new_y;

	new_x = data->player.x_pos + cos(data->player.angle * (PI / 180)) * STEP_SIZE;
	new_y = data->player.y_pos + sin(data->player.angle * (PI / 180)) * STEP_SIZE;
	if (data->parse->map[(int)(new_y / 64)][(int)(new_x / 64)] != '1')
	{
		data->player.x_pos = new_x;
		data->player.y_pos = new_y;
	}
}

void rotate_left(t_data *data)
{
	data->player.angle -= ROTATION_ANGLE;
	if (data->player.angle < 0)
		data->player.angle += 360;
}

void rotate_right(t_data *data)
{
	data->player.angle += ROTATION_ANGLE;
	if (data->player.angle > 360)
		data->player.angle -= 360;
}

int move(int key, void *da)
{
	t_data *data;

	data = (t_data *)da;
	if (key == ESC)
		endgame(data);
	if (key == W)
		move_forward(data);
	else if (key == S)
		move_backward(data);
	// else if (key == A)
	// 	move_left(data);
	// else if (key == D)
	// 	move_right(data);
	else if (key == LEFT)
		rotate_left(data);
	else if (key == RIGHT)
		rotate_right(data);
	else 
		return (0);
	init_rays(data);
	init_buffer(data);
	mlx_clear_window(data->mlx.mlx, data->mlx.window);
	start_ray_casting(data);
	return (0);
}
