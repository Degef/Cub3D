#include "../includes/cub3D.h"

int is_wall(double x, double y, char **map)
{
	if (x < 0 || x > CUBE_SIZE * 10 || y < 0 || y > CUBE_SIZE * 10)
		return (1);
	if (x > 0 && x < CUBE_SIZE * 10 && y > 0 && y < CUBE_SIZE * 10)
	{
		if (map[(int)(y / CUBE_SIZE)][(int)(x / CUBE_SIZE)] == '1')
			return (1);
	}
	return (0);
}

int pythagoras(t_ray *ray, double x, double y)
{
	int dist;

	dist = sqrt(pow(ray->pos.x - x, 2) + pow(ray->pos.y - y, 2));
	return (dist);
}

int find_h_ray_wall_hit(t_ray *ray, char **map, double x_to_check, double y_to_check)
{
	while (1 && ray->angle != 0 && ray->angle != 180)
	{
		x_to_check = ray->h_intercept.x;
		y_to_check = ray->h_intercept.y;
		if (ray->angle > 0 && ray->angle < 180)
			y_to_check -= 1;
		if (ray->angle > 180 && ray->angle < 360)
			y_to_check += 64;
		if (is_wall(x_to_check, y_to_check, map))
		{
			ray->h_wall_hit.x = x_to_check;
			ray->h_wall_hit.y = y_to_check;
			ray->h_wall_hit_flag = 1;
			ray->distance.x = pythagoras(ray, ray->h_wall_hit.x, ray->h_wall_hit.y);
			break ;
		}
		else
		{
			ray->h_intercept.x += ray->h_step.x;
			ray->h_intercept.y += ray->h_step.y;
		}
	}
	return (0);
}

int find_v_ray_wall_hit(t_ray *ray, char **map, double x_to_check, double y_to_check)
{
	while (1 && ray->angle != 90 && ray->angle != 270)
	{
		x_to_check = ray->v_intercept.x;
		y_to_check = ray->v_intercept.y;
		if (ray->angle > 90 && ray->angle < 270)
			x_to_check -= 1.00;
		if (ray->angle < 90 || ray->angle > 270)
			x_to_check += CUBE_SIZE;
		if (is_wall(x_to_check, y_to_check, map))
		{
			ray->v_wall_hit.x = x_to_check;
			ray->v_wall_hit.y = y_to_check;
			ray->v_wall_hit_flag = 1;
			ray->distance.y = pythagoras(ray, ray->v_wall_hit.x, ray->v_wall_hit.y);
			break ;
		}
		else
		{
			ray->v_intercept.x += ray->v_step.x;
			ray->v_intercept.y += ray->v_step.y;
		}
	}
	return (0);	
}

int find_vertical_intercept(t_ray *ray)
{
	if (ray->angle == 90 || ray->angle == 270)
		return (0);
	if (ray->angle > 90 && ray->angle < 270)
	{
		ray->v_intercept.x = floor(ray->pos.x / CUBE_SIZE) * CUBE_SIZE - 0.0001;
		ray->v_intercept.y = ray->pos.y + (ray->pos.x - ray->v_intercept.x) * tan(ray->angle * M_PI / 180);
		ray->v_step.x = - CUBE_SIZE;
		ray->v_step.y = -ray->v_step.x * tan(ray->angle * M_PI / 180);
	}
	else if (ray->angle < 90 || ray->angle > 270)
	{
		ray->v_intercept.x = floor(ray->pos.x / CUBE_SIZE) * CUBE_SIZE + CUBE_SIZE;
		ray->v_intercept.y = ray->pos.y + (ray->pos.x - ray->v_intercept.x) * tan(ray->angle * M_PI / 180);
		ray->v_step.x = CUBE_SIZE;
		ray->v_step.y = -ray->v_step.x * tan(ray->angle * M_PI / 180);
	}
	else
		return (0);
	return (0);
}

int find_horizontal_intercept(t_ray *ray)
{
	if (ray->angle == 0 || ray->angle == 180)
		return (0);
	if (ray->angle > 0 && ray->angle < 180)
	{
		ray->h_intercept.y = floor(ray->pos.y / CUBE_SIZE) * CUBE_SIZE - 0.0001;
		ray->h_intercept.x = ray->pos.x + (ray->pos.y - ray->h_intercept.y) / tan(ray->angle * M_PI / 180);
		ray->h_step.y = -CUBE_SIZE;
		ray->h_step.x = -ray->h_step.y / tan(ray->angle * M_PI / 180);
	}
	else if (ray->angle > 180 && ray->angle < 360)
	{
		ray->h_intercept.y = floor(ray->pos.y / CUBE_SIZE) * CUBE_SIZE + CUBE_SIZE;
		ray->h_intercept.x = ray->pos.x + (ray->pos.y - ray->h_intercept.y) / tan(ray->angle * M_PI / 180);
		ray->h_step.y = CUBE_SIZE;
		ray->h_step.x = -ray->h_step.y / tan(ray->angle * M_PI / 180);
	}
	else
		return (0);
	return (0);
}

int find_draw_start_end(t_ray *ray, t_data *data, int x)
{
	double wall_height;
	int		draw_start;
	int		draw_end;
	int		y;

	wall_height = ((CUBE_SIZE * WIN_H) / ray->ray_length) ;
	draw_start = (WIN_H / 2) - (wall_height / 2);
	if (draw_start < 0)
		draw_start = 0;
	draw_end = (WIN_H / 2) + (wall_height / 2);
	if (draw_end > WIN_H)
		draw_end = WIN_H;
	y = draw_start - 1;
	while (y < draw_end)
	{
		if ((y > -1 && y <= WIN_H) && (x > -1 && x <= WIN_W))
			data->buffer[y][x] = 0x8B0000;
		y++;
	}
	return (0);
}

int fix_fish_eye(t_ray *ray, double player_angle)
{
	double angle;

	angle = ray->angle - player_angle;
	if (angle < 0)
		angle += 360;
	if (angle > 360)
		angle -= 360;
	ray->ray_length = ray->ray_length * cos(angle * M_PI / 180);
	return (0);
}

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
				data->addr[i * WIN_W + j] = 0x87CEEB;
			else if (is_floor(data->buffer, i, j))
				data->addr[i * WIN_W + j] = 0xD2B48C;
			else
				data->addr[i * WIN_W + j] = data->buffer[i][j];

		}
	}
	return (0);
}

int start_ray_casting(t_data *data)
{
	int i;

	i = -1;
	while (++i < data->plane_width)
	{
		find_horizontal_intercept(&data->rays[i]);
		find_vertical_intercept(&data->rays[i]);
		find_h_ray_wall_hit(&data->rays[i], data->parse->map, data->rays[i].h_intercept.x, data->rays[i].h_intercept.y);
		find_v_ray_wall_hit(&data->rays[i], data->parse->map, data->rays[i].v_intercept.x, data->rays[i].v_intercept.y);
		if (data->rays[i].distance.x < data->rays[i].distance.y)
			data->rays[i].ray_length = data->rays[i].distance.x;
		else if (data->rays[i].angle == 90 || data->rays[i].angle == 270)
			data->rays[i].ray_length = data->rays[i].distance.x;
		else if (data->rays[i].angle == 0 || data->rays[i].angle == 180)
			data->rays[i].ray_length = data->rays[i].distance.y;
		else
			data->rays[i].ray_length = data->rays[i].distance.y;
		fix_fish_eye(&data->rays[i], data->player.angle);
		find_draw_start_end(&data->rays[i], data, i);
	}
	put_pixels(data);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.window, data->image, 0, 0);
	return (0);
}

int start_game(t_data *data)
{
	init_attributes(data);
	data->mlx.mlx = mlx_init();
	data->mlx.window = mlx_new_window(data->mlx.mlx, WIN_W, WIN_H, "Simple Window");
	data->image = mlx_new_image(data->mlx.mlx, WIN_W, WIN_H);
	data->addr = (int *)mlx_get_data_addr(data->image, &data->bits_per_pixel, &data->line_length, &data->endian);
	start_ray_casting(data);
	mlx_hook(data->mlx.window, 2, 0, &move, data);
	mlx_hook(data->mlx.window, 17, 1L << 17, &endgame, data);
    mlx_loop(data->mlx.mlx);
	return (0);
}
