/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Degef <dsium@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 16:13:30 by Degef             #+#    #+#             */
/*   Updated: 2023/09/20 19:05:53 by Degef            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	color_in_hex(char **splitted)
{
	int	arr[3];

	arr[0] = ft_atoi(splitted[0]) % 256;
	arr[1] = ft_atoi(splitted[1]) % 256;
	arr[2] = ft_atoi(splitted[2]) % 256;
	return ((arr[0] << 16) | (arr[1] << 8) | (arr[2]));
}

int	get_colors(t_parse *parse, char *color, int i)
{
	char	**splitted_color;

	splitted_color = ft_split(color + 1, ',');
	if (!splitted_color[0] || !splitted_color[1] || !splitted_color[2])
	{
		free_double_array(&splitted_color);
		if (parse->text[i][0] == 'C')
			return (printf("Error with ceil color\n"), -1);
		else
			return (printf("Error with floor\n"), -1);
	}
	if (parse->text[i][0] == 'F')
		parse->floor_color = color_in_hex(splitted_color);
	else
		parse->ceil_color = color_in_hex(splitted_color);
	free_double_array(&splitted_color);
	return (0);
}

int	get_elements(t_parse *parse, int i)
{
	while (parse->text[++i])
	{
		if (!ft_strncmp(parse->text[i], "NO", 2))
			parse->no_text = 
				ft_substr(parse->text[i], 3, ft_strlen(parse->text[i]) - 2);
		else if (!ft_strncmp(parse->text[i], "SO", 2))
			parse->so_text = 
				ft_substr(parse->text[i], 3, ft_strlen(parse->text[i]) - 2);
		else if (!ft_strncmp(parse->text[i], "WE", 2))
			parse->we_text = 
				ft_substr(parse->text[i], 3, ft_strlen(parse->text[i]) - 2);
		else if (!ft_strncmp(parse->text[i], "EA", 2))
			parse->ea_text = 
				ft_substr(parse->text[i], 3, ft_strlen(parse->text[i]) - 2);
		else if (parse->text[i][0] == 'F' || parse->text[i][0] == 'C')
			if (get_colors(parse, parse->text[i], i) == -1)
				return (0);
	}
	return (1);
}

void	get_map(t_parse *parse, int i, int j)
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
		parse->map[j++] = ft_strdup(parse->text[i++]);
	}
	parse->row = j;
}

int	parse_map(t_parse *parse)
{
	parse->no_text = NULL;
	parse->so_text = NULL;
	parse->we_text = NULL;
	parse->ea_text = NULL;
	parse->map = 0;
	if (!get_elements(parse, -1))
		return (0);
	get_map(parse, 0, 0);
	if (!map_valid(parse->map, parse))
		return (0);
	return (1);
}

	// int i = -1;
	// while (parse->map[++i])
	// 	printf("%s\n", parse->map[i]);
	// printf("map row: %zu, map colum: %zu\n", parse->row, parse->column);