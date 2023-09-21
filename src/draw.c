/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Degef <dsium@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 19:13:14 by Degef             #+#    #+#             */
/*   Updated: 2023/09/21 15:18:00 by Degef            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	is_ceiling(unsigned int **buffer, int i, int k)
{
	if (i == 0)
		return (1);
	while (--i > -1)
	{
		if (buffer[i][k] != 0)
			return (0);
	}
	return (1);
}

int	is_floor(unsigned int **buffer, int i, int k)
{
	if (i == 0)
		return (1);
	while (++i < WIN_H)
	{
		if (buffer[i][k] != 0)
			return (0);
	}
	return (1);
}

int	put_pixels(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (++i < WIN_H)
	{
		j = -1;
		while (++j < WIN_W)
		{
			if (is_ceiling(data->buffer, i, j))
				data->addr[i * WIN_W + j] = data->parse->ceil_color;
			else if (is_floor(data->buffer, i, j))
				data->addr[i * WIN_W + j] = data->parse->floor_color;
			else
				data->addr[i * WIN_W + j] = data->buffer[i][j];
			if (i > WIN_H / 2 - 8 && i < WIN_H / 2 + 8 && j == WIN_W / 2)
				data->addr[i * WIN_W + j] = 0x00FF00;
			if (j > WIN_W / 2 - 8 && j < WIN_W / 2 + 8 && i == WIN_H / 2)
				data->addr[i * WIN_W + j] = 0x00FF00;
		}
	}
	mlx_put_image_to_window(data->window.mlx, data->window.win,
		data->image, 0, 0);
	return (0);
}

// void draw_line(t_data *data, int x1, int y1, int x2, int y2, int color) {
//     int dx = abs(x2 - x1);
//     int dy = abs(y2 - y1);
//     int sx = (x1 < x2) ? 1 : -1;
//     int sy = (y1 < y2) ? 1 : -1;
//     int err = dx - dy;
//     int e2;

//     while (x1 != x2 || y1 != y2) {
// 		data->addr[y1 * data->window.map_width + x1] = color;
//         if (x1 == x2 && y1 == y2)
// 			break;
//         e2 = 2 * err;
//         if (e2 > -dy) {
//             err -= dy;
//             x1 += sx;
//         }
//         if (e2 < dx) {
//             err += dx;
//             y1 += sy;
//         }
//     }
// }

// void draw_player(t_data *data, int x, int y)
// {
//     int size = 5;  // Adjust the cube size as needed
//     int color = 0x00FF00;  // Green color (you can choose any color)
 
//     int i = -1;
// 	int j;
// 	while (++i < size)
// 	{
// 		j = -1;
// 		while ( ++j < size)
//             mlx_pixel_put(data->mlx, data->window, x + i, y + j, color);
// 	}
//     double x2 = x + data->delta_x*5;
//     double y2 = y + data->delta_y*5;
//     draw_line(data, x, y, x2, y2, color);
// }

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

// void draw_map(t_data *data, char **map, int x, int y)
// {
// 	int i, j;

// 	i = -1;
// 	while (++i < y)
// 	{
// 		j = -1;
// 		while (++j < x)
// 		{
// 			if (map[i/64][j/64] == '1')
// 				data->addr[i * x + j] = 0x00FFFFFF;
// 		}
// 	}
// 	draw_grid_lines(data, x, y);
// 	draw_player(data, data->player.x_pos, data->player.y_pos);
// 	// mlx_clear_window(data->window.mlx, data->window.win);
// }

