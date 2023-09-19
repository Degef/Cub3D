
#include "../includes/cub3D.h"

int		is_cubfile(char *file)
{
	int i;

	i = ft_strlen(file);
	if ( i < 5) 
		return (0);
	if (file[i - 4] != '.' || (file[i - 3] != 'c' || (file[i - 2] != 'u') || (file[i - 1] != 'b')))
		return (0);
	return (1);
}

void free_memory(t_parse *parse, t_data *data)
{
	if (parse->no_text)
		free(parse->no_text);
	if (parse->so_text)
		free(parse->so_text);
	if (parse->we_text)
		free(parse->we_text);
	if (parse->ea_text)
		free(parse->ea_text);
	if (parse->text)
		free_double_array(&parse->text);
	if (parse->map)
		free_double_array(&parse->map);
	// (void)data;
	if (data->buffer)
		free_double_array2(&data->buffer);
	// if (data->rays)
	// 	free(data->rays);
}

int start_game(t_data *data)
{
	init_attributes(data);
	data->window.mlx = mlx_init();
	data->window.win = mlx_new_window(data->window.mlx, WIN_W, WIN_H, "Simple Window");
	data->image = mlx_new_image(data->window.mlx, WIN_W, WIN_H);
	data->addr = (int *)mlx_get_data_addr(data->image, &data->bits_per_pixel, 
		&data->line_length, &data->endian);
	if (!get_texture(data->parse, data))
		return (0);
	start_ray_casting(data, &data->ray);
	mlx_hook(data->window.win, 2, 0, &move, data);
	mlx_hook(data->window.win, 17, 1L << 17, &endgame, data);
    mlx_loop(data->window.mlx);
	return (1);
}

int main(int argc, char **argv)
{
	t_data	data;
	t_parse	parse;

	if (argc < 2 || argc > 2)
		return(printf("Error! Wrong input. Usage (./Cub3d ./map/map.cub)\n"), 1);
	if (!is_cubfile(argv[1]))
		return (printf("Error! map is not .cub file\n"), 1);
	if (!read_map(&parse, argv[1]))
		return (1);
	if (!parse_map(&parse))
		return (free_memory(&parse, &data), 1);
	data.parse = &parse;
	if (!start_game(&data))
		return (free_memory(&parse, &data), 1);
	free_memory(&parse, &data);	
	return (0);
}
