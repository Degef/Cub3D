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
				data->x_pos = j * 64.00 + 32.00;
				data->y_pos = i * 64.00 + 32.00;
				if (data->parse->map[i][j] == 'E')
					data->angle = 0;
				if (data->parse->map[i][j] == 'N')
					data->angle = PI / 2;
				else if (data->parse->map[i][j] == 'W')
					data->angle = PI;
				else if (data->parse->map[i][j] == 'S')
					data->angle = 3 * PI / 2;
				data->parse->map[i][j] = '0';
				return (0);
			}
		}
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

	// data->player.height = 32;
	data->plane_width = data->parse->column * 64;
	data->plane_height = data->parse->row * 64;
	data->plane_dist = 277.128;
	// data->buffer = (unsigned int **)ft_calloc(data->plane_height, sizeof(unsigned int *));
	// i = -1;
	// while (++i < data->plane_height)
	// 	data->buffer[i] = (unsigned int *)ft_calloc(data->plane_width, sizeof(unsigned int));
	// init_buffer(data);
	find_player(data);
	data->deltaX = cos(data->angle)*5;
	data->deltaY = -sin(data->angle)*5;
	// init_rays(data);
	return (0);
}
