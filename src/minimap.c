/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Degef <dsium@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 15:32:32 by Degef             #+#    #+#             */
/*   Updated: 2023/09/21 19:24:20 by Degef            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	draw_player(t_data *data, int x, int y)
{
	int	size;
	int	color;
	int	i;
	int	j;

	i = -1;
	color = 0x00FF00;
	size = 5;
	while (++i < size)
	{
		j = -1;
		while (++j < size)
			data->mini_map.addr[(y + j)
				* data->parse->column * 8 + (x + i)] = color;
	}
}

int	draw_grid_lines(t_data *data, int win_width, int win_height, int color)
{
	int	x;
	int	y;

	x = 0;
	while (x < win_width)
	{
		y = -1;
		while (++y < win_height)
			data->mini_map.addr[y * win_width + x] = color;
		x += 8;
	}

	y = 0;
	while (y < win_height)
	{
		x = 0;
		while (++x < win_width)
			data->mini_map.addr[y * win_width + x] = color;
		y += 8;
	}
	return (0);
}

void	draw_mini_map(t_data *data, char **map, int x, int y)
{
	int	i;
	int	j;

	i = -1;
	while (++i < y)
	{
		j = -1;
		while (++j < x)
		{
			if (map[i / 8][j / 8] == '1')
				data->mini_map.addr[i * x + j] = 0x00FFFFFF;
			else
				data->mini_map.addr[i * x + j] = 0x00000000;
		}
	}
	// draw_grid_lines(data, x, y, 0x00000000);
	draw_player(data, data->player.x_pos / 64 * 8, data->player.y_pos / 64 * 8);
}
