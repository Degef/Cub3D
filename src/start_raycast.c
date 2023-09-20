/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_raycast.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Degef <dsium@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 18:30:59 by Degef             #+#    #+#             */
/*   Updated: 2023/09/20 19:20:28 by Degef            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	init_rays(t_data *data)
{
	data->ray.angle = data->player.angle + (FOV * PI / 180) / 2.0;
	if (data->ray.angle > 2 * PI)
		data->ray.angle -= 2 * PI;
	if (data->ray.angle < 0)
		data->ray.angle += 2 * PI;
	data->ray.x = data->player.x_pos;
	data->ray.y = data->player.y_pos;
	return (0);
}

int	fix_fish_eye(t_ray *ray, double player_angle)
{
	double	angle;

	angle = ray->angle - player_angle;
	if (angle < 0)
		angle += 2 * PI;
	if (angle > 2 * PI)
		angle -= 2 * PI;
	ray->ray_length = ray->ray_length * cos(angle);
	return (0);
}

void	select_ray2(t_data *data, t_ray *ray,
			int x_intercept, int y_intercept)
{
	if (data->previous == 'h')
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

void	select_ray(t_data *data, t_ray *ray,
			int x_intercept, int y_intercept)
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
	else
		select_ray2(data, ray, x_intercept, y_intercept);

}

int	start_ray_casting(t_data *data, t_ray *ray)
{
	int	i;
	int	x_intercept;
	int	y_intercept;

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
		ray->angle -= data->angle_increment;
		if (data->player.angle > 2 * PI)
			data->player.angle -= 2 * PI;
		if (data->ray.angle < 0)
			data->ray.angle += 2 * PI;
	}
	put_pixels(data);
	return (0);
}
