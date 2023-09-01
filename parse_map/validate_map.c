#include "../includes/cub3D.h"

int invalid_chars_present(char **map, int i, int j)
{
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] != '0' && map[i][j] != '1' && map[i][j] != 'E' 
				&& map[i][j] != 'W' && map[i][j] != 'N' && map[i][j] != 'S' && map[i][j] != 32)
			{
				printf("Error! Invalid character %c in map row:%d, colum:%d\n", map[i][j], i, j);
				return (1);
			}
		}
	}
	return (0);
}

int check_top_border(char **map, int i, int j)
{
	while (map[0][++i])
	{
		if (map[0][i] == '1')
			continue;
		else if (map[0][i] == 32)
		{
			while (map[j][i] == 32)
				j++;
			if (map[j][i] != '1')
				return (printf("Error! top border not closed.\n"), 1);
			j = 0;
		}
		else
			return (printf("Error! top border not closed\n"), 1);
	}
	return (0);
}

int check_bottom_border(char **map, t_parse *parse, int i, int j)
{
	while (map[parse->row][++i])
	{
		if (map[parse->row][i] == '1')
			continue;
		else if (map[parse->row][i] == 32)
		{
			while (map[j][i] == 32)
				j--;
			if (map[j][i] != '1')
				return (printf("Error! bottom border not closed.\n"), 1);
			j = parse->row;
		}
		else
			return (printf("Errorxx! bottom border not closed.\n"), 1);
	}
	return (0);
}

int check_left_border(char **map, int i, int j)
{
	while (map[++i])
	{
		if (map[i][0] == '1')
			continue;
		else if (map[i][0] == 32)
		{
			while (map[i][j] == 32)
				j++;
			if (!map[i][j] || map[i][j] != '1')
				return (printf("Error! left border not closed.\n"), 1);
			
		}
		else 
			return (printf("Error   ! left border not closed.\n"), 1);

	}
	return (0);
}

int check_right_border(char **map, int i, size_t j)
{
	while (map[++i])
	{
		j = ft_strlen(map[i]) - 1;
		if (map[i][j] == '1')
				continue;
		if (map[i][j] == 32)
		{
			while (map[i][j] == 32)
				j--;
			if (map[i][j] != '1')
				return (printf("Error! right border not closed.\n"), 1);
		}
		else 
			return (printf("Error! right border not closed.\n"), 1);

	}
	return (0);
}

int check_left_to_right(char **map, t_parse *parse, int i, int j)
{
	int check_next = 1;
	while (check_next && ++j < (int)parse->row)
	{
		check_next = 0;
		if (ft_strchr(map[j], 32))
			check_next = 1;
		while (map[j][++i])
		{
			if (map[j][i] == '1')
				continue ;
			else if (map[j][i] == 32)
			{
				while (map[j][i] == 32)
					i++;
				if (map[j][i] != '1')
					return (printf("Error! border not closed(left to right)\n"), 1);
			}
			else if (j > 0 && (map[j][i] == '0' || map[j][i] == 'E' 
						|| map[j][i] == 'W' || map[j][i] == 'N' || map[j][i] == 'S'))
				continue ;
		}
		i = -1;
	}
	return (0);
}

int map_valid(char **map, t_parse *parse)
{
	if (invalid_chars_present(map, -1, -1))
		return (0);
	if (check_top_border(map, -1, 0))
		return (0);
	if (check_bottom_border(map, parse, -1, parse->row))
		return (0);
	if (check_left_border(map, -1, 0))
		return (0);
	if (check_right_border(map, -1, 0))
		return (0);
	if (check_left_to_right(map, parse, -1, -1))
		return (0);
	return (1); 
}
