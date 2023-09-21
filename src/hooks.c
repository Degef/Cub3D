/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Degef <dsium@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 19:13:25 by Degef             #+#    #+#             */
/*   Updated: 2023/09/21 14:58:01 by Degef            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static void	move_forward(t_data *data)
{
	int	x;
	int	y;

	x = (int)(data->player.x_pos + data->player.delta_x * 2) / 64;
	y = (int)(data->player.y_pos + data->player.delta_y * 2) / 64;
	if (data->parse->map[y][x] == '1')
		return ;
	data->player.y_pos += data->player.delta_y;
	data->player.x_pos += data->player.delta_x;
}

static void	move_backward(t_data *data)
{
	int	x;
	int	y;

	x = (int)(data->player.x_pos - data->player.delta_x) / 64;
	y = (int)(data->player.y_pos - data->player.delta_y) / 64;
	if (data->parse->map[y][x] == '1')
		return ;
	data->player.y_pos -= data->player.delta_y;
	data->player.x_pos -= data->player.delta_x;
}

static void	move_left(t_data *data)
{
	int	x;
	int	y;

	x = (int)(data->player.x_pos + data->player.delta_y) / 64;
	y = (int)(data->player.y_pos - data->player.delta_x) / 64;
	if (data->parse->map[y][x] == '1')
		return ;
	data->player.x_pos += data->player.delta_y;
	data->player.y_pos -= data->player.delta_x;
}

static void	move_right(t_data *data)
{
	int	x;
	int	y;

	x = (int)(data->player.x_pos - data->player.delta_y) / 64;
	y = (int)(data->player.y_pos + data->player.delta_x) / 64;
	if (data->parse->map[y][x] == '1')
		return ;
	data->player.x_pos -= data->player.delta_y;
	data->player.y_pos += data->player.delta_x;
}

int	key_release(int key, void *da)
{
	t_data	*data;

	data = (t_data *)da;
	if (key == W)
		data->keys.w = 0;
	else if (key == S)
		data->keys.s = 0;
	else if (key == A)
		data->keys.a = 0;
	else if (key == D)
		data->keys.d = 0;
	else if (key == LEFT)
		data->keys.left = 0;
	else if (key == RIGHT)
		data->keys.right = 0;
	return (0);
}

int	keypress(int key, void *da)
{
	t_data	*data;

	data = (t_data *)da;
	if (key == ESC)
		endgame(data);
	else if (key == W)
		data->keys.w = 1;
	else if (key == S)
		data->keys.s = 1;
	else if (key == A)
		data->keys.a = 1;
	else if (key == D)
		data->keys.d = 1;
	else if (key == LEFT)
		data->keys.left = 1;
	else if (key == RIGHT)
		data->keys.right = 1;
	return (0);
}

int	main_loop(void *da)
{
	t_data	*data;

	data = (t_data *)da;
	if (data->keys.w)
		move_forward(data);
	if (data->keys.s)
		move_backward(data);
	if (data->keys.a)
		move_left(data);
	if (data->keys.d)
		move_right(data);
	if (data->keys.left)
		rotate_left(data);
	if (data->keys.right)
		rotate_right(data);
	start_ray_casting(data, &data->ray);
	return (0);
}
