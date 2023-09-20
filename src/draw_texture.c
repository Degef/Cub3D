/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Degef <dsium@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 18:48:38 by Degef             #+#    #+#             */
/*   Updated: 2023/09/20 19:13:08 by Degef            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

t_img	get_texture2(t_data *data, t_ray *ray)
{
	if (ray->h_wall_hit_flag && ray->angle > 0 && ray->angle < PI)
		return (data->texture = data->no_img);
	else if (ray->h_wall_hit_flag && ray->angle > PI && ray->angle < 2 * PI)
		return (data->texture = data->so_img);
	else if (ray->v_wall_hit_flag && ray->angle > PI / 2 
		&& ray->angle < 3 * PI / 2)
		return (data->texture = data->ea_img);
	else if (ray->v_wall_hit_flag && (ray->angle < PI / 2 
			|| ray->angle > 3 * PI / 2))
		return (data->texture = data->we_img);
	else if (ray->h_wall_hit_flag)
		return (data->texture = data->no_img);
	else if (ray->v_wall_hit_flag)
		return (data->texture = data->so_img);
	return (data->we_img);
}

double	texture_x(t_data *data, t_ray *ray)
{
	double	tex_x;

	if (ray->h_wall_hit_flag)
	{
		tex_x = (int)(ray->x_intercept) % data->texture.t_width;
		if (ray->angle > PI)
			tex_x = data->texture.t_width - tex_x - 1;
	}
	else
	{
		tex_x = (int)(ray->y_intercept) % data->texture.t_width;
		if (ray->angle < PI / 2.0 || ray->angle > 3 * PI / 2.0)
			tex_x = data->texture.t_width - tex_x - 1;
	}
	return (tex_x);
}

void	draw_wall(t_data *data, t_ray *ray, int x, int y)
{
	double	tex_x;
	double	step;
	double	tex_pos;
	int		tex_y;

	tex_x = texture_x(data, ray);
	step = data->texture.t_height / ray->wall_height;
	tex_pos = (ray->draw_start - (WIN_H / 2) + ray->wall_height / 2) * step;
	tex_y = (int)tex_pos & (data->texture.t_height - 1);
	while (y < ray->draw_end)
	{
		if ((y > -1 && y <= WIN_H) && (x > -1 && x <= WIN_W))
			data->buffer[y][x] = data->texture.addr[(tex_y * 64) + (int)tex_x];
		tex_pos += step;
		tex_y = (int)tex_pos & (data->texture.t_height - 1);
		y++;
	}
}

int	find_draw_start_end(t_ray *ray, t_data *data, int x)
{
	int		y;

	ray->wall_height = ((CUBE_SIZE * WIN_H) / ray->ray_length);
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
