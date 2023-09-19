#include "../includes/cub3D.h"

int init_rays(t_data *data)
{
	data->ray.angle = data->player.angle - (FOV * PI/180)/2.0;
	if (data->ray.angle > 2 * PI)
		data->ray.angle -= 2 * PI;
	if (data->ray.angle < 0)
		data->ray.angle += 2 * PI;
	data->ray.x = data->player.x_pos;
	data->ray.y = data->player.y_pos;
	return (0);
}

t_img get_texture2(t_data *data, t_ray *ray)
{
	if (ray->h_wall_hit_flag && ray->angle > 0 && ray->angle < PI)
		return (data->texture = data->no_img);
	else if (ray->h_wall_hit_flag && ray->angle > PI && ray->angle < 2 * PI)
		return (data->texture = data->so_img);
	else if (ray->v_wall_hit_flag && ray->angle > PI/2 && ray->angle < 3 * PI/2)
		return (data->texture = data->ea_img);
	else if (ray->v_wall_hit_flag && (ray->angle < PI/2 || ray->angle > 3 * PI/2))
		return (data->texture = data->we_img);
	else if (ray->h_wall_hit_flag)
		return (data->texture = data->no_img);
	else if (ray->v_wall_hit_flag)
		return (data->texture = data->so_img);
	return (data->we_img);
}

double	texture_x(t_data *data, t_ray *ray)
{
	double texX;

	if (ray->h_wall_hit_flag)
	{
		texX = (int)(ray->x_intercept) % data->texture.t_width;
		if (ray->angle > PI)
			texX = data->texture.t_width - texX - 1;
	}
	else
	{
		texX = (int)(ray->y_intercept) % data->texture.t_width;
		if (ray->angle < PI/2.0 || ray->angle > 3 * PI/2.0)
			texX = data->texture.t_width - texX - 1;
	}
	return (texX);
}

void draw_wall(t_data *data, t_ray *ray, int x, int y)
{
	double texX;

	texX = texture_x(data, ray);
	double step = data->texture.t_height / ray->wall_height;
	double texPos = (ray->draw_start - (WIN_H / 2) + ray->wall_height / 2) * step;
	int texY = (int)texPos & (data->texture.t_height - 1);
	while (y < ray->draw_end)
	{
		if ((y > -1 && y <= WIN_H) && (x > -1 && x <= WIN_W))
			data->buffer[y][x] = data->texture.addr[(texY * 64) + (int)texX];
		texPos += step;
		texY = (int)texPos & (data->texture.t_height - 1);
		y++;
	}
}

int find_draw_start_end(t_ray *ray, t_data *data, int x)
{
	int		y;

	ray->wall_height = ((CUBE_SIZE * WIN_H) / ray->ray_length) ;
	ray->draw_start = (WIN_H / 2) - (ray->wall_height / 2.0);
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = (WIN_H / 2) + (ray->wall_height / 2);
	if (ray->draw_end > WIN_H)
		ray->draw_end = WIN_H;
	y = ray->draw_start - 1;
	data->texture = get_texture2(data, ray);
	draw_wall(data, ray, x, y);
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

void select_ray(t_data *data, t_ray *ray, int x_intercept, int y_intercept)
{
	if (ray->h_distance < ray->v_distance && ray->h_wall_hit_flag)
	{
		ray->x_intercept = x_intercept;
		ray->y_intercept = y_intercept;
		ray->ray_length = ray->h_distance;
		ray->v_wall_hit_flag = 0;
		data->previous = 'h';
	}
	else if (ray->h_distance > ray->v_distance && ray->v_wall_hit_flag)
	{
		ray->ray_length = ray->v_distance;
		ray->h_wall_hit_flag = 0;
		data->previous = 'v';
	}
	else if (data->previous == 'h')
	{
		ray->x_intercept = x_intercept;
		ray->y_intercept = y_intercept;
		ray->ray_length = ray->h_distance;
		ray->v_wall_hit_flag = 0;
	}
	else if (data->previous == 'v')
	{
		ray->ray_length = ray->v_distance;
		ray->h_wall_hit_flag = 0;
	}
}

int start_ray_casting(t_data *data, t_ray *ray)
{
	int i;
	int x_intercept;
	int y_intercept;

	i = -1;
	init_rays(data);
	init_buffer(data);
	while (++i < WIN_W)
	{
		find_horizontal_intercept(ray, data->parse->map);
		x_intercept = ray->x_intercept;
		y_intercept = ray->y_intercept;
		find_vertical_intercept(ray, data->parse->map);
		select_ray(data, ray, x_intercept, y_intercept);
		fix_fish_eye(ray, data->player.angle);
		find_draw_start_end(ray, data, i);
		ray->angle += data->angle_increment;
		if (data->player.angle > 2 * PI)
			data->player.angle -= 2 * PI;
	}
	put_pixels(data);
	return (0);
}
