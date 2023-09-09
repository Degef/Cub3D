#include "../includes/cub3D.h"

int find_player(t_data *data)
{
	int i;
	int j;

	i = -1;
	while (++i < data->parse->num_lines)
	{
		j = -1;
		while (data->parse->map[i][++j])
		{
			if (data->parse->map[i][j] == 'N' || data->parse->map[i][j] == 'S' 
					|| data->parse->map[i][j] == 'E' || data->parse->map[i][j] == 'W')
			{
				data->player.x_pos = j * 64.00 + 32.00;
				data->player.y_pos = i * 64.00 + 32.00;
				data->player.x = j;
				data->player.y = i;
				if (data->parse->map[i][j] == 'E')
					data->player.angle = 0;
				if (data->parse->map[i][j] == 'N')
					data->player.angle = PI / 2;
				else if (data->parse->map[i][j] == 'W')
					data->player.angle = PI;
				else if (data->parse->map[i][j] == 'S')
					data->player.angle = 3 * PI / 2;
				data->parse->map[i][j] = '0';
				return (0);
			}
		}
	}
	return (0);
}

int init_rays(t_data *data)
{
	int i;
	double angle;

	i = -1;
	angle = data->player.angle - (FOV * PI/180)/2.0;
	while (++i < data->plane_width)
	{
		data->rays[i].angle = angle;
		data->rays[i].pos.x = data->player.x_pos;
		data->rays[i].pos.y = data->player.y_pos;
		data->rays[i].data = data;
		angle += data->angle_increment;
		if (angle > 2 * PI)
			angle -= 2 * PI;
	}
	return (0);
}

int init_buffer(t_data *data)
{
	int i;
	int j;

	i = 0;
	while (i < data->plane_height)
	{
		j = 0;
		while (j < data->plane_width)
		{
			data->buffer[i][j] = 0;
			j++;
		}
		i++;
	}
	return (0);
}

int init_attributes(t_data *data)
{
	// int i;

	data->player.height = 32;
	data->plane_width = data->parse->column * 64;
	data->plane_height = data->parse->row * 64;
	data->plane_dist = 277.128;
	data->angle_increment = (60.00 * PI / 180) / data->plane_width;
	data->rays = ft_calloc(data->plane_width + 1, sizeof(t_ray));
	// data->buffer = (unsigned int **)ft_calloc(data->plane_height, sizeof(unsigned int *));
	// i = -1;
	// while (++i < data->plane_height)
	// 	data->buffer[i] = (unsigned int *)ft_calloc(data->plane_width, sizeof(unsigned int));
	// init_buffer(data);
	find_player(data);
	data->player.deltaX = cos(data->player.angle)*5;
	data->player.deltaY = -sin(data->player.angle)*5;
	init_rays(data);
	return (0);
}
