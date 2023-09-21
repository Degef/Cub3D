/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Degef <dsium@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 19:34:33 by Degef             #+#    #+#             */
/*   Updated: 2023/09/21 17:04:39 by Degef            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	endgame(void *pa)
{
	t_data	*data;

	data = (t_data *)pa;
	mlx_destroy_window(data->window.mlx, data->window.win);
	mlx_destroy_image(data->window.mlx, data->image.img);
	mlx_destroy_image(data->window.mlx, data->mini_map.img);
	free_double_array2(&data->buffer);
	free_memory(data->parse, data);
	exit(0);
}

void	rotate_left(t_data *data)
{
	data->player.angle += ROTATION_ANGLE;
	if (data->player.angle < 0)
		data->player.angle += 2 * PI;
	data->player.delta_x = cos(data->player.angle) * STEP_SIZE;
	data->player.delta_y = -sin(data->player.angle) * STEP_SIZE;
}

void	rotate_right(t_data *data)
{
	data->player.angle -= ROTATION_ANGLE;
	if (data->player.angle > 2 * PI)
		data->player.angle -= 2 * PI;
	data->player.delta_x = cos(data->player.angle) * STEP_SIZE;
	data->player.delta_y = -sin(data->player.angle) * STEP_SIZE;
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
