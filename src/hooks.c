/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Degef <dsium@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 19:13:25 by Degef             #+#    #+#             */
/*   Updated: 2023/09/20 19:36:10 by Degef            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static void	move_forward(t_data *data)
{
	int	x;
	int	y;

	x = (int)(data->player.x_pos + data->player.delta_x) / 64;
	y = (int)(data->player.y_pos + data->player.delta_y) / 64;
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

int	move(int key, void *da)
{
	t_data	*data;

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
