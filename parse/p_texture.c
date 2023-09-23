/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_texture.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandom <aandom@student.abudhabi42.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 16:24:26 by aandom            #+#    #+#             */
/*   Updated: 2023/09/23 20:25:14 by aandom           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static unsigned long	convert_rgb_to_hex(int *rgb_tab)
{
	unsigned long	result;
	int				r;
	int				g;
	int				b;

	r = rgb_tab[0];
	g = rgb_tab[1];
	b = rgb_tab[2];
	result = ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
	return (result);
}

static int	check_valid_rgb(int *rgb)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (rgb[i] < 0 || rgb[i] > 255)
			return (print_err_val(rgb[i], "Invalid color", FAILURE));
		i++;
	}
	return (SUCCESS);
}

static char	*get_texture_path(char *line, int j)
{
	int		len;
	int		i;
	char	*path;

	while (line[j] && (line[j] == ' ' || line[j] == '\t'))
		j++;
	len = j;
	while (line[len] && (line[len] != ' ' && line[len] != '\t'))
		len++;
	path = malloc(sizeof(char) * (len - j + 1));
	if (!path)
		return (NULL);
	i = 0;
	while (line[j] && (line[j] != ' ' && line[j] != '\t' && line[j] != '\n'))
		path[i++] = line[j++];
	path[i] = '\0';
	while (line[j] && (line[j] == ' ' || line[j] == '\t'))
		j++;
	if (line[j] && line[j] != '\n')
	{
		free(path);
		path = NULL;
	}
	return (path);
}

int	fill_dir_tex(t_parse *parse, char *line, int j)
{
	if (line[j + 2] && ft_isprint(line[j + 2]))
		return (ERR);
	if (line[j] == 'N' && line[j + 1] == 'O' && !(parse->no_text))
		parse->no_text = get_texture_path(line, j + 2);
	else if (line[j] == 'S' && line[j + 1] == 'O' && !(parse->so_text))
		parse->so_text = get_texture_path(line, j + 2);
	else if (line[j] == 'W' && line[j + 1] == 'E' && !(parse->we_text))
		parse->we_text = get_texture_path(line, j + 2);
	else if (line[j] == 'E' && line[j + 1] == 'A' && !(parse->ea_text))
		parse->ea_text = get_texture_path(line, j + 2);
	else
		return (ERR);
	return (SUCCESS);
}

int	check_texture(t_parse *parse)
{
	if (!parse->no_text || !parse->so_text || !parse->we_text
		|| !parse->ea_text)
		return (print_err(parse->imap.path, "NO texture found", FAILURE));
	if (!parse->floor || !parse->ceiling)
		return (print_err(parse->imap.path, "NO color found", FAILURE));
	if (check_mapfile(parse->no_text, false) == FAILURE
		|| check_mapfile(parse->so_text, false) == FAILURE
		|| check_mapfile(parse->we_text, false) == FAILURE
		|| check_mapfile(parse->ea_text, false) == FAILURE
		|| check_valid_rgb(parse->floor) == FAILURE
		|| check_valid_rgb(parse->ceiling) == FAILURE)
		return (FAILURE);
	parse->floor_color = convert_rgb_to_hex(parse->floor);
	parse->ceil_color = convert_rgb_to_hex(parse->ceiling);
	free(parse->floor);
	free(parse->ceiling);
	return (SUCCESS);
}
