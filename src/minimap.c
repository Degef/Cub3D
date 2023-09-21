/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Degef <dsium@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 15:32:32 by Degef             #+#    #+#             */
/*   Updated: 2023/09/21 18:46:41 by Degef            ###   ########.fr       */
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

void	draw_map(t_data *data, char **map, int x, int y)
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
	draw_player(data, data->player.x_pos / 64 * 8, data->player.y_pos / 64 * 8);
}

void	draw_mini_map(t_data *data)
{
	draw_map(data, data->parse->map, data->parse->column * 8, data->parse->row * 8);
}

// void draw_grid_lines(t_data *data, int win_width, int win_height)
// {
// 	int color = 0x00000000;
// 	int x = 0;
// 	int y;

// 	while (x < win_width)
// 	{
// 		y = -1;
// 		while (++y < win_height)
//             mlx_pixel_put(data->mlx, data->window, x, y, color);
// 		x += 64;
// 	}

// 	y = 0;
// 	while (y < win_height)
// 	{
// 		x = 0;
// 		while (++x < win_width)
//             mlx_pixel_put(data->mlx, data->window, x, y, color);
// 		y += 64;
// 	}
// }

// int draw_grid_lines(t_data *data, int win_width, int win_height)
// {
// 	int color = 0x00000000;
// 	int x = 0;
// 	int y;

// 	while (x < win_width)
// 	{
// 		y = -1;
// 		while (++y < win_height)
// 			data->addr[y * win_width + x] = color;
// 		x += 64;
// 	}

// 	y = 0;
// 	while (y < win_height)
// 	{
// 		x = 0;
// 		while (++x < win_width)
// 			data->addr[y * win_width + x] = color;
// 		y += 64;
// 	}
// 	return (0);
// }

// int draw_player(t_data *data, int x, int y)
// {
// 	int size = 5;  // Adjust the cube size as needed
// 	int color = 0x00FF00;  // Green color (you can choose any color)
// 	int i = -1;
// 	int j;

// 	while (++i < size)
// 	{
// 		j = -1;
// 		while ( ++j < size)
// 			data->addr[(y + j) * WIN_W + (x + i)] = color;
// 	}
// 	return (0);
// }
