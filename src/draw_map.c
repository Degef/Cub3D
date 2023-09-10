#include "../includes/cub3D.h"


static void move_forward(t_data *data)
{
	data->player.y_pos += data->player.deltaY;
	data->player.x_pos += data->player.deltaX;
}

static void move_backward(t_data *data)
{
	data->player.y_pos -= data->player.deltaY;
	data->player.x_pos -= data->player.deltaX;
}

static void move_left(t_data *data)
{
	data->player.angle += 0.1;
	if (data->player.angle > 2 * PI)
		data->player.angle -= 2 * PI;
	data->player.deltaX = cos(data->player.angle)*5;
	data->player.deltaY = -sin(data->player.angle)*5;
}

static void move_right(t_data *data)
{
	data->player.angle -= 0.1;
	if (data->player.angle < 0)
		data->player.angle += 2 * PI;
	data->player.deltaX = cos(data->player.angle)*5;
	data->player.deltaY = -sin(data->player.angle)*5;
}

void draw_line(t_data *data, int x1, int y1, int x2, int y2, int color) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;
    int e2;

    while (x1 != x2 || y1 != y2) {
        mlx_pixel_put(data->mlx.mlx, data->mlx.window, x1, y1, color);
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

// void	draw_line(t_data *data, int x1, int y1, int x2, int y2, int color)
// {
// 	// int	x1;
// 	// int	y1;
// 	// int	x2;
// 	// int	y2;

// 	// x1 = arr[0];
// 	// y1 = arr[2];
// 	// x2 = arr[1];
// 	// y2 = arr[3];
// 	init_vals(cub, (int []){x1, y1, x2, y2});
// 	while (x1 != x2 || y1 != y2)
// 	{
// 		my_mlx_pixel_put(cub, x1, y1, color);
// 		cub->ray_c.err2 = 2 * cub->ray_c.err;
// 		if (cub->ray_c.err2 > -cub->ray_c.dy)
// 		{
// 			cub->ray_c.err -= cub->ray_c.dy;
// 			x1 += cub->ray_c.sx;
// 		}
// 		if (cub->ray_c.err2 < cub->ray_c.dx)
// 		{
// 			cub->ray_c.err += cub->ray_c.dx;
// 			y1 += cub->ray_c.sy;
// 		}
// 	}
// }


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
            mlx_pixel_put(data->mlx.mlx, data->mlx.window, x + i, y + j, color);
	}
    double x2 = x + data->player.deltaX*5;
    double y2 = y + data->player.deltaY*5;
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
            mlx_pixel_put(data->mlx.mlx, data->mlx.window, x, y, color);
		x += 64;
	}

	y = 0;
	while (y < win_height)
	{
		x = 0;
		while (++x < win_width)
            mlx_pixel_put(data->mlx.mlx, data->mlx.window, x, y, color);
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
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.window, data->image, 0, 0);
	draw_grid_lines(data, x, y);
}

// void draw_rays(t_data *data, int n_rays, int i)
// {
// 	i = -1;
// 	while (++i < n_rays)
// 	{
// 		// printf("i = %d, angle = %f\n", i, data->rays[i].angle);
// 		// if (data->rays[i].angle != 3.141593)
// 		draw_line(data, data->player.x_pos, data->player.y_pos, data->rays[i].wall_hit.x, data->rays[i].wall_hit.y, 0xFF0000);
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
	mlx_clear_window(data->mlx.mlx, data->mlx.window);
	draw_map(data, data->parse->map, data->parse->column*64, data->parse->row*64);
	draw_player(data, data->player.x_pos, data->player.y_pos);
	start_ray_casting(data, &data->ray);
	// draw_rays(data, data->plane_width, 0);
	return (0);
}
