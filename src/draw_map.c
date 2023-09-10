#include "../includes/cub3D.h"


static void move_forward(t_data *data)
{
	data->y_pos += data->deltaY;
	data->x_pos += data->deltaX;
}

static void move_backward(t_data *data)
{
	data->y_pos -= data->deltaY;
	data->x_pos -= data->deltaX;
}

static void move_left(t_data *data)
{
	data->angle += 0.04;
	if (data->angle > 2 * PI)
		data->angle -= 2 * PI;
	data->deltaX = cos(data->angle)*5;
	data->deltaY = -sin(data->angle)*5;
}

static void move_right(t_data *data)
{
	data->angle -= 0.04;
	if (data->angle < 0)
		data->angle += 2 * PI;
	data->deltaX = cos(data->angle)*5;
	data->deltaY = -sin(data->angle)*5;
}

void draw_line(t_data *data, int x1, int y1, int x2, int y2, int color) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;
    int e2;

    while (x1 != x2 || y1 != y2) {
        mlx_pixel_put(data->mlx, data->window, x1, y1, color);
        if (x1 == x2 && y1 == y2)
			break;
        e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y1 += sy;
        }
    }
}

void draw_player(t_data *data, int x, int y)
{
    int size = 5;  // Adjust the cube size as needed
    int color = 0x00FF00;  // Green color (you can choose any color)
 
    int i = -1;
	int j;
	while (++i < size)
	{
		j = -1;
		while ( ++j < size)
            mlx_pixel_put(data->mlx, data->window, x + i, y + j, color);
	}
    double x2 = x + data->deltaX*5;
    double y2 = y + data->deltaY*5;
    draw_line(data, x, y, x2, y2, color);
}

void draw_grid_lines(t_data *data, int win_width, int win_height)
{
	int color = 0x00000000;
	int x = 0;
	int y;

	while (x < win_width)
	{
		y = -1;
		while (++y < win_height)
            mlx_pixel_put(data->mlx, data->window, x, y, color);
		x += 64;
	}

	y = 0;
	while (y < win_height)
	{
		x = 0;
		while (++x < win_width)
            mlx_pixel_put(data->mlx, data->window, x, y, color);
		y += 64;
	}
}

void draw_map(t_data *data, char **map, int x, int y)
{
	int i, j;

	i = -1;
	while (++i < y)
	{
		j = -1;
		while (++j < x)
		{
			if (map[i/64][j/64] == '1')
				data->addr[i * x + j] = 0x00FFFFFF;
		}
	}
	mlx_put_image_to_window(data->mlx, data->window, data->image, 0, 0);
	draw_grid_lines(data, x, y);
}

// void draw_rays(t_data *data, int n_rays, int i)
// {
// 	i = -1;
// 	while (++i < n_rays)
// 	{
// 		// printf("i = %d, angle = %f\n", i, data->rays[i].angle);
// 		// if (data->rays[i].angle != 3.141593)
// 		draw_line(data, data->x_pos, data->y_pos, data->rays[i].wall_hit.x, data->rays[i].wall_hit.y, 0xFF0000);
// 	}
// }

int move_player(int key, void *da)
{
	t_data *data;

	data = (t_data *)da;
	if (key == ESC)
		endgame(data);
	if (key == W)
		move_forward(data);
	else if (key == S)
		move_backward(data);
	else if (key == A)
		move_left(data);
	else if (key == D)
		move_right(data);
	else 
		return (0);
	// init_rays(data);
	mlx_clear_window(data->mlx, data->window);
	draw_map(data, data->parse->map, data->parse->column*64, data->parse->row*64);
	draw_player(data, data->x_pos, data->y_pos);
	start_ray_casting(data, &data->ray);
	// draw_rays(data, data->plane_width, 0);
	return (0);
}
