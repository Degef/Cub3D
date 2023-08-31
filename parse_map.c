#include "../includes/cub3D.h"

void get_colors(t_parse *parse, i)
{
	
}

void init_parse(t_parse *parse, int i)
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
			get_colors(parse, i);
	}
}

int parse_map(t_parse *parse)
{
	init_parse(parse, -1);
	return (1);
}