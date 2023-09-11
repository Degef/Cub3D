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