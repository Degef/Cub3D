#include "../includes/cub3D.h"

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
				data->player.x_pos = j * 64.00 + 32.00;
				data->player.y_pos = i * 64.00 + 32.00;
				data->player.x = j;
				data->player.y = i;
				data->player.angle = 0;
				if (data->parse->map[i][j] == 'N')
					data->player.angle = 90;
				else if (data->parse->map[i][j] == 'W')
					data->player.angle = 180;
				else if (data->parse->map[i][j] == 'S')
					data->player.angle = 270;
				data->parse->map[i][j] = 0;
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
	angle = data->player.angle - (FOV / 2.00);
	while (i < data->plane_width)
	{
		data->rays[i].angle = angle;
		data->rays[i].pos.x = data->player.x_pos;
		data->rays[i].pos.y = data->player.y_pos;
		i++;
		angle += data->angle_increment;
	}
	return (0);
}

int init_buffer(t_data *data)
{
	int i;
	int j;

	i = 0;
	while (i < WIN_H)
	{
		j = 0;
		while (j < WIN_W)
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
	int i;

	data->player.height = 32;
	data->plane_width = WIN_W;
	data->plane_height = WIN_H;
	data->plane_dist = 277.128;
	data->angle_increment = 60.00 / WIN_W;
	data->rays = ft_calloc(WIN_W + 1, sizeof(t_ray));
	data->buffer = (unsigned int **)ft_calloc(WIN_H, sizeof(unsigned int *));
	i = -1;
	while (++i < WIN_H)
		data->buffer[i] = (unsigned int *)ft_calloc(WIN_W, sizeof(unsigned int));
	init_buffer(data);
	find_player(data);
	init_rays(data);
	return (0);
}