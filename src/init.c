#include "../includes/cub3D.h"

int	mark_player(t_data *data, int i, int j)
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
				return (mark_player(data, i, j));
		}
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

	data->plane_width = data->parse->column*64;
	data->plane_height = data->parse->row*64;
	data->plane_dist = 277.128;
	data->ray.data = data;
	data->angle_increment = (60.00 * PI / 180) / data->plane_width;
	data->buffer = (unsigned int **)ft_calloc(WIN_H, sizeof(unsigned int *));
	i = -1;
	while (++i < data->plane_height)
		data->buffer[i] = (unsigned int *)ft_calloc(WIN_W, sizeof(unsigned int));
	find_player(data);
	data->deltaX = cos(data->angle)*STEP_SIZE;
	data->deltaY = -sin(data->angle)*STEP_SIZE;
	return (0);
}
