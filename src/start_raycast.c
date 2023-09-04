#include "../includes/cub3D.h"

int endgame(void *pa)
{
	t_data *data;

	data = (t_data *)pa;

	mlx_destroy_window(data->mlx.mlx, data->mlx.window);
	free_memory(data->parse);
	exit(0);
}


int move(int key, void *da)
{
	t_data *data;

	data = (t_data *)da;
	if (key == 53)
		endgame(data);
	return (0);
}

int find_player(t_data *data)
{
	int i;
	int j;

	i = 0;
	while (i < data->parse->num_lines)
	{
		j = 0;
		while (data->parse->map[i][j])
		{
			if (data->parse->map[i][j] == 'N' || data->parse->map[i][j] == 'S' 
					|| data->parse->map[i][j] == 'E' || data->parse->map[i][j] == 'W')
			{
				data->player.x_pos = j * 64 + 32;
				data->player.y_pos = i * 64 + 32;
				data->player.x = j;
				data->player.y = i;
				data->player.angle = 0;
				if (data->parse->map[i][j] == 'S')
					data->player.angle = 90;
				else if (data->parse->map[i][j] == 'W')
					data->player.angle = 180;
				else if (data->parse->map[i][j] == 'N')
					data->player.angle = 270;
				return (0);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int init_rays(t_data *data)
{
	int i;
	double angle;

	i = 0;
	angle = data->player.angle - (data->player.fov / 2);
	while (i < data->plane_width)
	{
		data->rays[i].angle = angle;
		data->rays[i].x = data->player.x_pos;
		data->rays[i].y = data->player.y_pos;
		i++;
		angle += data->angle_increment;
	}
	return (0);
}

int init_attributes(t_data *data)
{
	data->player.fov = 60;
	data->player.height = 32;
	data->plane_width = 320;
	data->plane_height = 200;
	data->plane_dist = 277.128;
	data->angle_increment = 0.1875;
	find_player(data);
	init_rays(data);
	return (0);
}

int is_wall(double x, double y, char **map)
{
	if (x < 0 || x > 64 * 10 || y < 0 || y > 64 * 10)
		return (1);
	if (x > 0 && x < 64 * 10 && y > 0 && y < 64 * 10)
	{
		if (map[(int)(y / 64)][(int)(x / 64)] == '1')
			return (1);
	}
	return (0);
}

int pythagoras(t_ray *ray, double x, double y)
{
	int dist;

	dist = sqrt(pow(ray->x - x, 2) + pow(ray->y - y, 2));
	return (dist);
}

int find_h_ray_wall_hit(t_ray *ray, char **map, double x_to_check, double y_to_check)
{
	while (1)
	{
		x_to_check = ray->h_x_intercept;
		y_to_check = ray->h_y_intercept;
		if (ray->angle > 0 && ray->angle < 180)
			y_to_check -= 0.0001;
		if (ray->angle > 180 && ray->angle < 360)
			y_to_check += 64;
		if (is_wall(x_to_check, y_to_check, map))
		{
			ray->h_wall_hit_x = x_to_check;
			ray->h_wall_hit_y = y_to_check;
			ray->h_wall_hit = 1;
			ray->h_distance = pythagoras(ray, ray->h_wall_hit_x, ray->h_wall_hit_y);
			break ;
		}
		else
		{
			ray->h_x_intercept += ray->h_x_step;
			ray->h_y_intercept += ray->h_y_step;
		}
	}
	return (0);
}

int find_v_ray_wall_hit(t_ray *ray, char **map, double x_to_check, double y_to_check)
{
	while (1)
	{
		x_to_check = ray->v_x_intercept;
		y_to_check = ray->v_y_intercept;
		if (ray->angle > 90 && ray->angle < 270)
			x_to_check -= 0.0001;
		if (ray->angle < 90 || ray->angle > 270)
			x_to_check += 64;
		if (is_wall(x_to_check, y_to_check, map))
		{
			ray->v_wall_hit_x = x_to_check;
			ray->v_wall_hit_y = y_to_check;
			ray->v_wall_hit = 1;
			ray->v_distance = pythagoras(ray, ray->v_wall_hit_x, ray->v_wall_hit_y);
			break ;
		}
		else
		{
			ray->v_x_intercept += ray->v_x_step;
			ray->v_y_intercept += ray->v_y_step;
		}
	}
	return (0);	
}

int find_horizontal_intercept(t_ray **rays, int plane_width)
{
	int i;

	i = -1;
	while (++i < plane_width)
	{
		if ((*rays)[i].angle == 0 || (*rays)[i].angle == 180)
			continue ;
		if ((*rays)[i].angle > 0 && (*rays)[i].angle < 180)
		{
			(*rays)[i].h_y_intercept = floor((*rays)[i].y / 64) * 64 - 0.0001;
			(*rays)[i].h_x_intercept = (*rays)[i].x + ((*rays)[i].y - (*rays)[i].h_y_intercept) / tan((*rays)[i].angle * M_PI / 180);
			(*rays)[i].h_y_step = -64;
			(*rays)[i].h_x_step = -(*rays)[i].h_y_step / tan((*rays)[i].angle * M_PI / 180);
		}
		else if ((*rays)[i].angle > 180 && (*rays)[i].angle < 360)
		{
			(*rays)[i].h_y_intercept = floor((*rays)[i].y / 64) * 64 + 64;
			(*rays)[i].h_x_intercept = (*rays)[i].x + ((*rays)[i].y - (*rays)[i].h_y_intercept) / tan((*rays)[i].angle * M_PI / 180);
			(*rays)[i].h_y_step = 64;
			(*rays)[i].h_x_step = -(*rays)[i].h_y_step / tan((*rays)[i].angle * M_PI / 180);
		}
		else
			return (0);
	}
}

int find_vertical_intercept(t_ray **rays, int plane_width)
{
	int i;

	i = -1;
	while (++i < plane_width)
	{
		if ((*rays)[i].angle == 90 || (*rays)[i].angle == 270)
			continue ;
		if ((*rays)[i].angle > 90 && (*rays)[i].angle < 270)
		{
			(*rays)[i].v_x_intercept = floor((*rays)[i].x / 64) * 64 - 0.0001;
			(*rays)[i].v_y_intercept = (*rays)[i].y + ((*rays)[i].x - (*rays)[i].v_x_intercept) * tan((*rays)[i].angle * M_PI / 180);
			(*rays)[i].v_x_step = -64;
			(*rays)[i].v_y_step = -(*rays)[i].v_x_step * tan((*rays)[i].angle * M_PI / 180);
		}
		else if ((*rays)[i].angle < 90 || (*rays)[i].angle > 270)
		{
			(*rays)[i].v_x_intercept = floor((*rays)[i].x / 64) * 64 + 64;
			(*rays)[i].v_y_intercept = (*rays)[i].y + ((*rays)[i].x - (*rays)[i].v_x_intercept) * tan((*rays)[i].angle * M_PI / 180);
			(*rays)[i].v_x_step = 64;
			(*rays)[i].v_y_step = -(*rays)[i].v_x_step * tan((*rays)[i].angle * M_PI / 180);
		}
		else
			return (0);
	}
}

// int do_ray_casting(t_data *data)
// {
// 	find_horizontal_intercept(&data->rays, data->plane_width);
// 	find_vertical_intercept(&data->rays, data->plane_width);
// 	int i = -1;
// 	while (++i < data->plane_width)
// 		find_ray_wall_hit(&data->rays[i], data->parse->map);
// 	return (0);
// }

int start_game(t_data *data)
{
	init_attributes(data);
	data->mlx.mlx = mlx_init();
	data->mlx.window = mlx_new_window(data->mlx.mlx, data->plane_width, data->plane_height, "Simple Window");
	do_ray_casting(data);
	mlx_hook(data->mlx.window, 2, 0, &move, data);
	mlx_hook(data->mlx.window, 17, 1L << 17, &endgame, data);
    mlx_loop(data->mlx.mlx);
	return (0);
}
