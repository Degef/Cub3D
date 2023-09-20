#include "../includes/cub3D.h"

int endgame(void *pa)
{
	t_data *data;

	data = (t_data *)pa;

	mlx_destroy_window(data->window.mlx, data->window.win);
	mlx_destroy_image(data->window.mlx, data->image);
	free_double_array2(&data->buffer);
	free_memory(data->parse, data);
	exit(0);
}

static void move_forward(t_data *data)
{
	int x;
	int y;

	x = (int)(data->player.x_pos + data->player.delta_x) / 64;
	y = (int)(data->player.y_pos + data->player.delta_y) / 64;
	if (data->parse->map[y][x] == '1')
		return ;
	data->player.y_pos += data->player.delta_y;
	data->player.x_pos += data->player.delta_x;
}

static void move_backward(t_data *data)
{
	int x;
	int y;

	x = (int)(data->player.x_pos - data->player.delta_x) / 64;
	y = (int)(data->player.y_pos - data->player.delta_y) / 64;
	if (data->parse->map[y][x] == '1')
		return ;
	data->player.y_pos -= data->player.delta_y;
	data->player.x_pos -= data->player.delta_x;
}

static void move_left(t_data *data)
{
	int x;
	int y;

	x = (int)(data->player.x_pos - data->player.delta_y) / 64;
	y = (int)(data->player.y_pos + data->player.delta_x) / 64;
	if (data->parse->map[y][x] == '1')
		return ;
	data->player.y_pos += data->player.delta_x;
	data->player.x_pos -= data->player.delta_y;
}

static void move_right(t_data *data)
{
	int x;
	int y;

	x = (int)(data->player.x_pos + data->player.delta_y) / 64;
	y = (int)(data->player.y_pos - data->player.delta_x) / 64;
	if (data->parse->map[y][x] == '1')
		return ;
	data->player.y_pos -= data->player.delta_x;
	data->player.x_pos += data->player.delta_y;
}

static void rotate_left(t_data *data)
{
	data->player.angle -= ROTATION_ANGLE;
	if (data->player.angle > 2 * PI)
		data->player.angle -= 2 * PI;
	data->player.delta_x = cos(data->player.angle)*STEP_SIZE;
	data->player.delta_y = -sin(data->player.angle)*STEP_SIZE;
}

static void rotate_right(t_data *data)
{
	data->player.angle += ROTATION_ANGLE;
	if (data->player.angle < 0)
		data->player.angle += 2 * PI;
	data->player.delta_x = cos(data->player.angle)*STEP_SIZE;
	data->player.delta_y = -sin(data->player.angle)*STEP_SIZE;
}

int move(int key, void *da)
{
	t_data *data;

	data = (t_data *)da;
	if (key == ESC)
		endgame(data);
	else if (key == W)
		move_forward(data);
	else if (key == S)
		move_backward(data);
	else if (key == A)
		move_left(data);
	else if (key == D)
		move_right(data);
	else if (key == LEFT)
		rotate_left(data);
	else if (key == RIGHT)
		rotate_right(data);
	else 
		return (0);
	start_ray_casting(data, &data->ray);
	return (0);
}
