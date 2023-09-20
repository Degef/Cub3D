/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Degef <dsium@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 18:55:16 by Degef             #+#    #+#             */
/*   Updated: 2023/09/20 18:57:10 by Degef            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	mark_player(t_data *data, int i, int j)
{
	data->player.x_pos = j * 64.00 + 32.00;
	data->player.y_pos = i * 64.00 + 32.00;
	if (data->parse->map[i][j] == 'E')
		data->player.angle = 0;
	if (data->parse->map[i][j] == 'N')
		data->player.angle = PI / 2;
	else if (data->parse->map[i][j] == 'W')
		data->player.angle = PI;
	else if (data->parse->map[i][j] == 'S')
		data->player.angle = 3 * PI / 2;
	data->parse->map[i][j] = '0';
	return (0);
}

int	find_player(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (++i < data->parse->num_lines)
	{
		j = -1;
		while (data->parse->map[i][++j])
		{
			if (data->parse->map[i][j] == 'N' 
					|| data->parse->map[i][j] == 'S' 
					|| data->parse->map[i][j] == 'E'
					|| data->parse->map[i][j] == 'W')
				return (mark_player(data, i, j));
		}
	}
	return (0);
}

int	init_buffer(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < WIN_H)
	{
		j = 0;
		while (j < WIN_W)
		{
			data->buffer[i][j] = 0;
			j++;
		}
		i++;
	}
	return (0);
}

int	init_attributes(t_data *data)
{
	int	i;

	data->window.map_width = data->parse->column * 64;
	data->window.map_height = data->parse->row * 64;
	data->ray.data = data;
	data->angle_increment = (FOV * PI / 180) / WIN_W;
	data->buffer = (unsigned int **)ft_calloc(WIN_H + 1,
			sizeof(unsigned int *));
	i = -1;
	while (++i < WIN_H)
		data->buffer[i] = (unsigned int *)ft_calloc(WIN_W,
				sizeof(unsigned int));
	find_player(data);
	data->player.delta_x = cos(data->player.angle) * STEP_SIZE;
	data->player.delta_y = -sin(data->player.angle) * STEP_SIZE;
	return (0);
}
