#include "../includes/cub3D.h"

int		is_cubfile(char *file)
{
	int i;

	i = ft_strlen(file);
	if (file[i - 4] != '.' || (file[i - 3] != 'c' || (file[i - 2] != 'u') || (file[i - 1] != 'b')))
		return (0);
	return (1);
}

// int validate_map(t_data **data)
// {

// }

int main(int argc, char **argv)
{
	t_parse	parse;

	if (argc < 2 || argc > 2)
		return(printf("Error! Wrong input. Usage (./Cub3d ./map/map.cub)\n"), 1);
	if (!is_cubfile(argv[1]))
		return (printf("Error! map is not .cub file\n"), 1);
	if (!read_map(&parse, argv[1]))
		return (1);
	if (!parse_map(&parse))
		return (1);
	
	free_double_array(&parse.text, parse.num_lines);
	return (0);
}
