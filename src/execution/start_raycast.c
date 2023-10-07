/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_raycast.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Degef <dsium@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 18:30:59 by Degef             #+#    #+#             */
/*   Updated: 2023/10/06 20:53:34 by Degef            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

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
	ray->intercepts[0] = ray->x_intercept / 64 * 8;
	ray->intercepts[1] = ray->y_intercept / 64 * 8;
}

void	draw_game(t_data *data)
{
	put_pixels(data);
	mlx_put_image_to_window(data->window.mlx, data->window.win,
		data->image.img, 0, 0);
	mlx_put_image_to_window(data->window.mlx, data->window.win,
		data->mini_map.img, 0, 0);
}

void	start_initializers(t_data *data)
{
	init_rays(data);
	init_buffer(data);
	draw_mini_map(data, data->parse->map, data->parse->column * 8,
		data->parse->row * 8);
}

/*
This function is called in main_loop, the purpose of this function is to start
the raycasting. First, it calls start_initializers to initialize the rays 
and the buffer. Then, it loops through the width of the screen
and calls find_horizontal_intercept and find_vertical_intercept to 
find the intercepts of the rays Then, it calls select_ray to select the
ray with the shortest distance
Then, it calls fix_fish_eye to fix the fish eye effect
Then, it calls find_draw_start_end to find the start and end of the rays
Then, it calls draw_ray to draw the rays for the mini map
After finishing the loop, it calls draw_game to draw the game
*/ 

int	cast_rays(t_data *data, t_ray *ray)
{
	int	i;
	int	x_intercept;
	int	y_intercept;

	i = -1;
	start_initializers(data);
	while (++i < WIN_W)
	{
		find_horizontal_intercept(ray, data->parse->map);
		x_intercept = ray->x_intercept;
		y_intercept = ray->y_intercept;
		find_vertical_intercept(ray, data->parse->map);
		select_ray(data, ray, x_intercept, y_intercept);
		fix_fish_eye(ray, data->player.angle);
		find_draw_start_end(ray, data, i);
		draw_ray(data, ray->x / 64 * 8, ray->y / 64 * 8, ray->intercepts);
		ray->angle -= data->angle_increment;
		if (data->player.angle > 2 * PI)
			data->player.angle -= 2 * PI;
		if (data->ray.angle < 0)
			data->ray.angle += 2 * PI;
	}
	draw_game(data);
	return (0);
}
