/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_text_utilis.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Degef <dsium@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 17:53:51 by aandom            #+#    #+#             */
/*   Updated: 2023/10/06 20:53:34 by Degef            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static bool	no_digit(char *str)
{
	int		i;
	bool	found_no_digit;

	i = 0;
	found_no_digit = true;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 1)
			found_no_digit = false;
		i++;
	}
	return (found_no_digit);
}

static int	*copy_into_rgb_array(char **rgb_to_convert, int *rgb)
{
	int		i;

	i = -1;
	while (rgb_to_convert[++i])
	{
		rgb[i] = ft_atoi(rgb_to_convert[i]);
		if (rgb[i] == -1 || no_digit(rgb_to_convert[i]) == true)
		{
			void_free_arr((void **)rgb_to_convert);
			free(rgb);
			return (0);
		}
	}
	void_free_arr((void **)rgb_to_convert);
	return (rgb);
}

static int	*set_rgb_colors(char *line)
{
	char	**rgb_to_convert;
	int		*rgb;
	int		count;

	rgb_to_convert = ft_split(line, ',');
	count = 0;
	while (rgb_to_convert[count])
		count++;
	if (count != 3)
	{
		void_free_arr((void **)rgb_to_convert);
		return (0);
	}
	rgb = malloc(sizeof(int) * 3);
	if (!rgb)
	{
		print_err(NULL, "Could not allocate Memory", 0);
		return (0);
	}
	return (copy_into_rgb_array(rgb_to_convert, rgb));
}

int	fill_color_textures(t_parse *parse, char *line, int j)
{
	if (line[j + 1] && ft_isprint(line[j + 1]))
		return (print_err(parse->imap.path, "Invalid color", ERR));
	if (!parse->ceiling && line[j] == 'C')
	{
		parse->ceiling = set_rgb_colors(line + j + 1);
		if (parse->ceiling == 0)
			return (print_err(parse->imap.path, "Invalid ceiling color", ERR));
	}
	else if (!parse->floor && line[j] == 'F')
	{
		parse->floor = set_rgb_colors(line + j + 1);
		if (parse->floor == 0)
			return (print_err(parse->imap.path, "Invalid floor color", ERR));
	}
	else
		return (print_err(parse->imap.path, "Invalid Color", ERR));
	return (SUCCESS);
}
