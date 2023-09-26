/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Degef <dsium@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 19:13:25 by Degef             #+#    #+#             */
/*   Updated: 2023/09/26 16:54:27 by Degef            ###   ########.fr       */
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
	x = (int)(data->player.x_pos + data->player.delta_x) / 64;
	y = (int)(data->player.y_pos + data->player.delta_y) / 64;
	if (data->parse->map[(int)data->player.y_pos / 64][x] == '1'
		&& data->parse->map[y][(int)data->player.x_pos / 64] == '1')
		return ;
	data->player.y_pos += data->player.delta_y;
	data->player.x_pos += data->player.delta_x;
}

static void	move_backward(t_data *data)
{
	int	x;
	int	y;

	x = (int)(data->player.x_pos - data->player.delta_x * 2) / 64;
	y = (int)(data->player.y_pos - data->player.delta_y * 2) / 64;
	if (data->parse->map[y][x] == '1')
		return ;
	x = (int)(data->player.x_pos - data->player.delta_x) / 64;
	y = (int)(data->player.y_pos - data->player.delta_y) / 64;
	if (data->parse->map[(int)data->player.y_pos / 64][x] == '1'
		&& data->parse->map[y][(int)data->player.x_pos / 64] == '1')
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
