/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Degef <dsium@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 19:34:33 by Degef             #+#    #+#             */
/*   Updated: 2023/09/20 20:33:07 by Degef            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	endgame(void *pa)
{
	t_data	*data;

	data = (t_data *)pa;

	mlx_destroy_window(data->window.mlx, data->window.win);
	mlx_destroy_image(data->window.mlx, data->image);
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
