#include "../includes/cub3D.h"

int is_wall(t_ray *ray, double x, double y, char **map)
{
	if (x > 0 && x < ray->data->plane_width && y > 0 && y < ray->data->plane_height)
	{
		if (map[((int)y>>6)][((int)x>>6)] == '1')
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

// int find_draw_start_end(t_ray *ray, t_data *data, int x)
// {
// 	double wall_height;
// 	int		draw_start;
// 	int		draw_end;
// 	int		y;

// 	wall_height = ((CUBE_SIZE * data->plane_width) / ray->ray_length) ;
// 	draw_start = (data->plane_width / 2) - (wall_height / 2);
// 	if (draw_start < 0)
// 		draw_start = 0;
// 	draw_end = (data->plane_width / 2) + (wall_height / 2);
// 	if (draw_end > data->plane_width)
// 		draw_end = data->plane_width;
// 	y = draw_start - 1;
// 	while (y < draw_end)
// 	{
// 		if ((y > -1 && y <= data->plane_width) && (x > -1 && x <= WIN_W))
// 			data->buffer[y][x] = 0x8B0000;
// 		y++;
// 	}
// 	return (0);
// }

// int fix_fish_eye(t_ray *ray, double player_angle)
// {
// 	double angle;

// 	angle = ray->angle - player_angle;
// 	if (angle < 0)
// 		angle += 2*PI;
// 	if (angle > 2*PI)
// 		angle -= 2*PI;
// 	ray->ray_length = ray->ray_length * cos(angle);
// 	return (0);
// }

// int	is_ceiling(unsigned int **buffer, int i, int k)
// {
// 	if (i == 0)
// 		return (1);
// 	while (--i > -1)
// 	{
// 		if (buffer[i][k] != 0)
// 			return (0);
// 	}
// 	return (1);
// }

// int	is_floor(unsigned int **buffer, int i, int k)
// {
// 	if (i == 0)
// 		return (1);
// 	while (++i < WIN_H)
// 	{
// 		if (buffer[i][k] != 0)
// 			return (0);
// 	}
// 	return (1);
// }

// int put_pixels(t_data *data)
// {
// 	int i;
// 	int j;

// 	i = -1;
// 	while (++i < WIN_H)
// 	{
// 		j = -1;
// 		while (++j < WIN_W)
// 		{
// 			if (is_ceiling(data->buffer, i, j))
// 				data->addr[i * WIN_W + j] = 0x87CEEB;
// 			else if (is_floor(data->buffer, i, j))
// 				data->addr[i * WIN_W + j] = 0xD2B48C;
// 			else
// 				data->addr[i * WIN_W + j] = data->buffer[i][j];

// 		}
// 	}
// 	return (0);
// }

int find_v_ray_wall_hit(t_ray *ray, char **map, double x_offset, double y_offset)
{
	int num = -1;
	while (++num < 15)
	{
		if (cos(ray->angle) > 0.0001)
			ray->x_intercept += 0.001;
		else if (cos(ray->angle) < -0.0001)
			ray->x_intercept -= 0.001; 
		if (is_wall(ray, ray->x_intercept, ray->y_intercept, map))
		{
			ray->v_wall_hit_flag = 1;
			ray->v_distance = pythagoras(ray, ray->x_intercept, ray->y_intercept);
			break ;
		}
		else
		{
			ray->x_intercept += x_offset;
			ray->y_intercept += y_offset;
		}
	}
	return (0);	
}

int find_vertical_intercept(t_ray *ray, char **map)
{
	ray->v_distance = 100000;
	double Tan = tan(ray->angle);
	double x_offset = 0.0;
	double y_offset = 0.0;
	if (cos(ray->angle) > 0.001) //looking right
	{
		ray->x_intercept = (((int)ray->x>>6)<<6) + CUBE_SIZE;
		ray->y_intercept = (ray->x - ray->x_intercept) * Tan + ray->y;
		x_offset = CUBE_SIZE;
		y_offset = -CUBE_SIZE * Tan;
	}
	else if (cos(ray->angle) < -0.001)
	{
		ray->x_intercept = (((int)ray->x>>6)<<6) - 0.001;
		ray->y_intercept = (ray->x - ray->x_intercept) * Tan + ray->y;
		x_offset = -CUBE_SIZE;
		y_offset = CUBE_SIZE * Tan;
	}
	find_v_ray_wall_hit(ray, map, x_offset, y_offset);
	return (0);
}

int find_h_ray_wall_hit(t_ray *ray, char **map, double x_offset, double y_offset)
{
	int num = 0;
	while (++num < 15)
	{
		if (ray->angle > 0 && ray->angle < PI)
			ray->y_intercept -= 0.0001;
		if (ray->angle > PI && ray->angle < 2*PI)
			ray->y_intercept += 0.0001;
		if (is_wall(ray, ray->x_intercept, ray->y_intercept, map))
		{
			ray->h_wall_hit_flag = 1;
			ray->h_distance = pythagoras(ray, ray->x_intercept, ray->y_intercept);
			break ;
		}
		else
		{
			ray->x_intercept += x_offset;
			ray->y_intercept += y_offset;
		}
	}
	return (0);
}

int find_horizontal_intercept(t_ray *ray, char **map)
{
	double Tan = 1.0/tan(ray->angle);
	double x_offset = 0.0;
	double y_offset = 0.0;
	ray->h_distance = 100000;
	if (sin(ray->angle) > 0)
	{
		ray->y_intercept = (((int)ray->y>>6)<<6) - 0.0001;
		ray->x_intercept = ray->x + (ray->y - ray->y_intercept) * Tan;
		y_offset = -CUBE_SIZE;
		x_offset = CUBE_SIZE * Tan;
	}
	else if (sin(ray->angle) < 0) 
	{
		ray->y_intercept = (((int)ray->y>>6)<<6) + CUBE_SIZE;
		ray->x_intercept = ray->x + (ray->y - ray->y_intercept) * Tan;
		y_offset = CUBE_SIZE;
		x_offset = -CUBE_SIZE * Tan;
	}
	find_h_ray_wall_hit(ray, map, x_offset, y_offset);
	return (0);
}

int init_rays(t_data *data)
{
	int i;

	i = -1;
	data->ray.angle = data->angle - (FOV * PI/180)/2.0;
	if (data->ray.angle > 2 * PI)
		data->ray.angle -= 2 * PI;
	data->ray.x = data->x_pos;
	data->ray.y = data->y_pos;
	data->ray.data = data;
	data->angle_increment = (60.00 * PI / 180) / 60;
	return (0);
}

int start_ray_casting(t_data *data, t_ray *ray)
{
	int i;
	double hx;
	double hy;

	i = -1;
	init_rays(data);
	while (++i < 60)
	{
		find_horizontal_intercept(ray, data->parse->map);
		hx = ray->x_intercept;
		hy = ray->y_intercept;
		find_vertical_intercept(ray, data->parse->map);
		if (ray->h_distance <= ray->v_distance && ray->h_wall_hit_flag)
		{
			ray->x_intercept = hx;
			ray->y_intercept = hy;
			ray->ray_length = ray->h_distance;
		}
		else if (ray->h_distance > ray->v_distance && ray->v_wall_hit_flag)
			ray->ray_length = ray->v_distance;	
		draw_line(data, data->x_pos, data->y_pos, ray->x_intercept, ray->y_intercept, 0xFF0000);
		ray->angle += data->angle_increment;
	}
	return (0);
}

int start_game(t_data *data)
{
	init_attributes(data);
	data->mlx = mlx_init();
	data->window = mlx_new_window(data->mlx, data->parse->column*64, data->parse->row*64, "Simple Window");
	data->image = mlx_new_image(data->mlx, data->parse->column*64, data->parse->row*64);
	data->addr = (int *)mlx_get_data_addr(data->image, &data->bits_per_pixel, &data->line_length, &data->endian);
	draw_map(data, data->parse->map, data->parse->column*64, data->parse->row*64);
	draw_player(data, data->x_pos, data->y_pos);
	start_ray_casting(data, &data->ray);
	mlx_hook(data->window, 2, 0, &move_player, data);
	mlx_hook(data->window, 17, 1L << 17, &endgame, data);
    mlx_loop(data->mlx);
	return (0);
}
