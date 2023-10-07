/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Degef <dsium@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 19:13:14 by Degef             #+#    #+#             */
/*   Updated: 2023/10/06 20:53:34 by Degef            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	is_wall(t_ray *ray, double x, double y, char **map)
{
	if (x > 0 && x < ray->data->window.map_width
		&& y > 0 && y < ray->data->window.map_height)
	{
		if (map[((int)y >> 6)][((int)x >> 6)] == '1')
			return (1);
	}
	return (0);
}

int	pythagoras(t_ray *ray, double x, double y)
{
	int	dist;

	dist = sqrt(pow(ray->x - x, 2) + pow(ray->y - y, 2));
	return (dist);
}

int	get_texture(t_parse *parse, t_data *data)
{
	data->no_img.img = mlx_xpm_file_to_image(data->window.mlx,
			parse->no_text, &data->no_img.t_width, &data->no_img.t_height);
	data->so_img.img = mlx_xpm_file_to_image(data->window.mlx, parse->so_text,
			&data->so_img.t_width, &data->so_img.t_height);
	data->we_img.img = mlx_xpm_file_to_image(data->window.mlx, parse->we_text,
			&data->we_img.t_width, &data->we_img.t_height);
	data->ea_img.img = mlx_xpm_file_to_image(data->window.mlx, parse->ea_text,
			&data->ea_img.t_width, &data->ea_img.t_height);
	if (!data->no_img.img || !data->so_img.img || !data->we_img.img 
		|| !data->ea_img.img)
		return (printf("Error! Texture not found\n"), 0); 
	data->no_img.addr = (int *)mlx_get_data_addr(data->no_img.img,
			&data->no_img.bpp, &data->no_img.line_length, &data->no_img.endian);
	data->so_img.addr = (int *)mlx_get_data_addr(data->so_img.img,
			&data->so_img.bpp, &data->so_img.line_length, &data->so_img.endian);
	data->we_img.addr = (int *)mlx_get_data_addr(data->we_img.img,
			&data->we_img.bpp, &data->we_img.line_length, &data->we_img.endian);
	data->ea_img.addr = (int *)mlx_get_data_addr(data->ea_img.img,
			&data->ea_img.bpp, &data->ea_img.line_length, &data->ea_img.endian);
	return (1);
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
