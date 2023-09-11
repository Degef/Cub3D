#include "../includes/cub3D.h"

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