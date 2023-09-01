#include "../includes/cub3D.h"

int get_colors(t_parse *parse, char *color, int i)
{
	char **splitted_color;

	splitted_color = ft_split(color + 1, ',');
	if (!splitted_color[0] || !splitted_color[1] || !splitted_color[2])
	{
		parse->error = BADCEIL;
		if (parse->text[i][0] == 'F')
			parse->error = BADFLOOR;
		return (-1);
	}
	if (parse->text[i][0] == 'F')
	{
		parse->floor[0] = ft_atoi(splitted_color[0]) % 255;
		parse->floor[1] = ft_atoi(splitted_color[2]) % 255;
		parse->floor[2] = ft_atoi(splitted_color[1]) % 255;
	}
	else
	{
		parse->ceil[0] = ft_atoi(splitted_color[0]) % 255;
		parse->ceil[1] = ft_atoi(splitted_color[2]) % 255;
		parse->ceil[2] = ft_atoi(splitted_color[1]) % 255;
	}
	return (0);
}

void get_elements(t_parse *parse, int i)
{
	parse->no_text = 0;
	parse->so_text = 0;
	parse->we_text = 0;
	parse->ea_text = 0;

	while (parse->text[++i])
	{
		if (!ft_strncmp(parse->text[i], "NO", 2))
			parse->no_text = ft_substr(parse->text[i], 2, ft_strlen(parse->text[i]) - 2);
		else if (!ft_strncmp(parse->text[i], "SO", 2))
			parse->so_text = ft_substr(parse->text[i], 2, ft_strlen(parse->text[i]) - 2);
		else if (!ft_strncmp(parse->text[i], "WE", 2))
			parse->we_text = ft_substr(parse->text[i], 2, ft_strlen(parse->text[i]) - 2);
		else if (!ft_strncmp(parse->text[i], "EA", 2))
			parse->ea_text = ft_substr(parse->text[i], 2, ft_strlen(parse->text[i]) - 2);
		else if (parse->text[i][0] == 'F' || parse->text[i][0] == 'C')
			if (get_colors(parse, parse->text[i], i) == -1)
				return ;
	}
}

void get_map(t_parse *parse, int i, int j)
{
	while (parse->text[i][0] == 'N' || parse->text[i][0] == 'S' 
			|| parse->text[i][0] == 'E' || parse->text[i][0] == 'W' 
			|| parse->text[i][0] == '\n' || parse->text[i][0] == 'F' 
			|| parse->text[i][0] == 'C')
		i++;
	parse->map = ft_calloc(parse->num_lines - i + 1, sizeof(char *));
	parse->column = 0;
	parse->row = 0;
	while (parse->text[i])
	{
		if (ft_strlen(parse->text[i]) > parse->column)
			parse->column = ft_strlen(parse->text[i]);
		parse->map[j++] = parse->text[i++];
	}
	parse->row = j - 1;
}

int parse_map(t_parse *parse)
{
	get_elements(parse, -1);
	get_map(parse, 0, 0);
	int i = -1;
	while (parse->map[++i])
		printf("%s\n", parse->map[i]);
	printf("map row: %zu, map colum: %zu\n", parse->row, parse->column);
	if (!map_valid(parse->map, parse))
		return (0);
	return (1);
}
