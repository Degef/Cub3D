/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Degef <dsium@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 18:57:28 by Degef             #+#    #+#             */
/*   Updated: 2023/09/26 17:02:52 by Degef            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3D.h"

int	is_cubfile(char *file)
{
	int	i;

	i = ft_strlen(file);
	if (i < 5)
		return (0);
	if (file[i - 4] != '.' || (file[i - 3] != 'c'
			|| (file[i - 2] != 'u') || (file[i - 1] != 'b')))
		return (0);
	return (1);
}

void	free_memory(t_parse *parse, t_data *data)
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
	(void)data;
}


//this function is called in main_loop
int	start_game(t_data *data)
{
	init_attributes(data);
	data->window.mlx = mlx_init();
	data->window.win = mlx_new_window(data->window.mlx, WIN_W, WIN_H, "Cub3D");
	data->image.img = mlx_new_image(data->window.mlx, WIN_W, WIN_H);
	data->image.addr = (int *)mlx_get_data_addr(data->image.img,
			&data->image.bpp, 
			&data->image.line_length, &data->image.endian);
	data->mini_map.img = mlx_new_image(data->window.mlx,
			data->parse->column * 8, data->parse->row * 8);
	data->mini_map.addr = (int *)mlx_get_data_addr(data->mini_map.img,
			&data->mini_map.bpp,
			&data->mini_map.line_length, &data->mini_map.endian);
	if (!get_texture(data->parse, data))
		return (0);
	start_ray_casting(data, &data->ray);
	mlx_hook(data->window.win, X_EVENT_KEY_PRESS, 0, &keypress, data);
	mlx_hook(data->window.win, X_EVENT_KEY_RELEASE, 0, &key_release, data);
	mlx_hook(data->window.win, X_EVENT_EXIT, 1L << 17, &endgame, data);
	mlx_loop_hook(data->window.mlx, &main_loop, data);
	mlx_loop(data->window.mlx);
	(void) data;
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	data;
	t_parse	parse;

	if (argc < 2 || argc > 2)
		return (printf("Wrong input. Usage (./Cub3d ./map/map.cub)\n"), 1);
	if (!ft_parse(&parse, argv[1])) 
		return (EXIT_FAILURE);
	data.parse = &parse;
	if (!start_game(&data))
		return (free_memory(&parse, &data), 1);
	free_memory(&parse, &data);
	return (0);
}
