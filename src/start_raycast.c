#include "../includes/cub3D.h"

int init_rays(t_data *data)
{
	data->ray.angle = data->angle - (FOV * PI/180)/2.0;
	if (data->ray.angle > 2 * PI)
		data->ray.angle -= 2 * PI;
	if (data->ray.angle < 0)
		data->ray.angle += 2 * PI;
	data->ray.x = data->x_pos;
	data->ray.y = data->y_pos;
	return (0);
}

int find_draw_start_end(t_ray *ray, t_data *data, int x)
{
	double wall_height;
	int		draw_start;
	int		draw_end;
	int		y;

	wall_height = ((CUBE_SIZE * WIN_H) / ray->ray_length) ;
	draw_start = (WIN_H / 2) - (wall_height / 2.0);
	if (draw_start < 0)
		draw_start = 0;
	draw_end = (WIN_H / 2) + (wall_height / 2);
	if (draw_end > WIN_H)
		draw_end = WIN_H;
	y = draw_start - 1;
	while (y < draw_end)
	{
		if ((y > -1 && y <= WIN_H) && (x > -1 && x <= data->plane_width))
			data->buffer[y][x] = 0x5d478b;
		y++;
	}
	return (0);
}

int fix_fish_eye(t_ray *ray, double player_angle)
{
	double angle;

	angle = ray->angle - player_angle;
	if (angle < 0)
		angle += 2*PI;
	if (angle > 2*PI)
		angle -= 2*PI;
	ray->ray_length = ray->ray_length * cos(angle);
	return (0);
}

int start_ray_casting(t_data *data, t_ray *ray)
{
	int i;

	i = -1;
	init_rays(data);
	init_buffer(data);
	while (++i < WIN_W)
	{
		find_horizontal_intercept(ray, data->parse->map);
		find_vertical_intercept(ray, data->parse->map);
		if (ray->h_distance <= ray->v_distance && ray->h_wall_hit_flag)
			ray->ray_length = ray->h_distance;
		else if (ray->h_distance > ray->v_distance && ray->v_wall_hit_flag)
			ray->ray_length = ray->v_distance;
		fix_fish_eye(ray, data->angle);
		find_draw_start_end(ray, data, i);
		ray->angle += data->angle_increment;
		if (data->angle > 2 * PI)
			data->angle -= 2 * PI;
	}
	put_pixels(data);
	return (0);
}

int start_game(t_data *data)
{
	init_attributes(data);
	data->mlx = mlx_init();
	data->window = mlx_new_window(data->mlx, WIN_W, WIN_H, "Simple Window");
	data->image = mlx_new_image(data->mlx, WIN_W, WIN_H);
	data->addr = (int *)mlx_get_data_addr(data->image, &data->bits_per_pixel, 
		&data->line_length, &data->endian);
	start_ray_casting(data, &data->ray);
	mlx_hook(data->window, 2, 0, &move, data);
	mlx_hook(data->window, 17, 1L << 17, &endgame, data);
    mlx_loop(data->mlx);
	return (0);
}
