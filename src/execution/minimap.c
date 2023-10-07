/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Degef <dsium@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 15:32:32 by Degef             #+#    #+#             */
/*   Updated: 2023/10/06 20:53:34 by Degef            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	init_vars(t_data *data, int x1, int y1, int *pos2)
{
	data->draw_line.dx = abs(pos2[0] - x1);
	data->draw_line.dy = abs(pos2[1] - y1);
	data->draw_line.sx = -1;
	if (x1 < pos2[0])
		data->draw_line.sx = 1;
	data->draw_line.sy = -1;
	if (y1 < pos2[1])
		data->draw_line.sy = 1;
	data->draw_line.err = data->draw_line.dx - data->draw_line.dy;
}

void	draw_ray(t_data *data, int x1, int y1, int *pos2)
{
	init_vars(data, x1, y1, pos2);
	while (x1 != pos2[0] || y1 != pos2[1])
	{
		data->mini_map.addr[y1 * data->parse->column * 8 + x1] = 0x74DF00;
		if (x1 == pos2[0] && y1 == pos2[1])
			break ;
		data->draw_line.e2 = 2 * data->draw_line.err;
		if (data->draw_line.e2 > -data->draw_line.dy)
		{
			data->draw_line.err -= data->draw_line.dy;
			x1 += data->draw_line.sx;
		}
		if (data->draw_line.e2 < data->draw_line.dx)
		{
			data->draw_line.err += data->draw_line.dx;
			y1 += data->draw_line.sy;
		}
	}
}

void	draw_player(t_data *data, int x, int y)
{
	int	size;
	int	i;
	int	j;

	i = -1;
	size = 3;
	while (++i < size)
	{
		j = -1;
		while (++j < size)
			data->mini_map.addr[(y + j)
				* data->parse->column * 8 + (x + i)] = 0x00FF00;
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
				data->mini_map.addr[i * x + j] = 0x0489B1;
			else
				data->mini_map.addr[i * x + j] = 0x00000000;
		}
	}
	draw_grid_lines(data, x, y, 0x00000000);
	draw_player(data, data->player.x_pos / 64 * 8, data->player.y_pos / 64 * 8);
}
