#include "../includes/cub3D.h"

int endgame(void *pa)
{
	t_data *data;

	data = (t_data *)pa;

	mlx_destroy_window(data->mlx, data->window);
	free_memory(data->parse, data);
	exit(0);
}

static void move_forward(t_data *data)
{
	int x;
	int y;

	x = (int)(data->x_pos + data->deltaX) / 64;
	y = (int)(data->y_pos + data->deltaY) / 64;
	if (data->parse->map[y][x] == '1')
		return ;
	data->y_pos += data->deltaY;
	data->x_pos += data->deltaX;
}

static void move_backward(t_data *data)
{
	int x;
	int y;

	x = (int)(data->x_pos - data->deltaX) / 64;
	y = (int)(data->y_pos - data->deltaY) / 64;
	if (data->parse->map[y][x] == '1')
		return ;
	data->y_pos -= data->deltaY;
	data->x_pos -= data->deltaX;
}

static void move_left(t_data *data)
{
	int x;
	int y;

	x = (int)(data->x_pos - data->deltaY) / 64;
	y = (int)(data->y_pos + data->deltaX) / 64;
	if (data->parse->map[y][x] == '1')
		return ;
	data->y_pos += data->deltaX;
	data->x_pos -= data->deltaY;
}

static void move_right(t_data *data)
{
	int x;
	int y;

	x = (int)(data->x_pos + data->deltaY) / 64;
	y = (int)(data->y_pos - data->deltaX) / 64;
	if (data->parse->map[y][x] == '1')
		return ;
	data->y_pos -= data->deltaX;
	data->x_pos += data->deltaY;
}

static void rotate_left(t_data *data)
{
	data->angle -= ROTATION_ANGLE;
	if (data->angle > 2 * PI)
		data->angle -= 2 * PI;
	data->deltaX = cos(data->angle)*STEP_SIZE;
	data->deltaY = -sin(data->angle)*STEP_SIZE;
}

static void rotate_right(t_data *data)
{
	data->angle += ROTATION_ANGLE;
	if (data->angle < 0)
		data->angle += 2 * PI;
	data->deltaX = cos(data->angle)*5;
	data->deltaY = -sin(data->angle)*5;
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
	mlx_clear_window(data->mlx, data->window);
	start_ray_casting(data, &data->ray);
	return (0);
}
