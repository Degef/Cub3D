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

int put_pixels(t_data *data)
{
	int i;
	int j;

	i = -1;
	while (++i < WIN_H)
	{
		j = -1;
		while (++j < WIN_W)
		{
			if (is_ceiling(data->buffer, i, j))
				data->addr[i * WIN_W + j] = 0xadd8e6;
			else if (is_floor(data->buffer, i, j))
				data->addr[i * WIN_W + j] = 0x4B6C57;
			else
				data->addr[i * WIN_W + j] = data->buffer[i][j];
		}
	}
	mlx_put_image_to_window(data->mlx, data->window, data->image, 0, 0);
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
//         mlx_pixel_put(data->mlx, data->window, x1, y1, color);
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
//     double x2 = x + data->deltaX*5;
//     double y2 = y + data->deltaY*5;
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
// 	mlx_put_image_to_window(data->mlx, data->window, data->image, 0, 0);
// 	draw_grid_lines(data, x, y);
// }

