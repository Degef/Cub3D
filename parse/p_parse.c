/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_parse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandom <aandom@student.abudhabi42.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 19:18:22 by aandom            #+#    #+#             */
/*   Updated: 2023/09/23 21:43:47 by aandom           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static bool	check_cub_file(char *arg)
{
	size_t	len;

	len = ft_strlen(arg);
	if ((arg[len - 3] != 'c' || arg[len - 2] != 'u'
			|| arg[len - 1] != 'b'
			|| arg[len - 4] != '.'))
		return (false);
	return (true);
}

static bool	check_xmp_file(char *arg)
{
	size_t	len;

	len = ft_strlen(arg);
	if ((arg[len - 3] != 'x' || arg[len - 2] != 'p'
			|| arg[len - 1] != 'm'
			|| arg[len - 4] != '.'))
		return (false);
	return (true);
}

static bool	is_dir(char *arg)
{
	int		fd;
	bool	ret;

	ret = false;
	fd = open(arg, O_DIRECTORY);
	if (fd >= 0)
	{
		close (fd);
		ret = true;
	}
	return (ret);
}

int	check_mapfile(char *arg, bool cub)
{
	int	fd;

	if (is_dir(arg))
		return (print_err(arg, "is Directory", 1));
	fd = open(arg, O_RDONLY);
	if (fd == -1)
		return (print_err(arg, strerror(errno), 1));
	close(fd);
	if (cub && !check_cub_file(arg))
		return (print_err(arg, "not a .cub file", 1));
	if (!cub && !check_xmp_file(arg))
		return (print_err(arg, "not a .xmp file", 1));
	return (0);
}

int	ft_parse(t_parse *parse, char *path)
{
	if (check_mapfile(path, true) == 1)
		return (SUCCESS);
	parse->pdir = '\0';
	initialize_imap(&parse->imap);
	parse_map_file(path, parse);
	if (parse->imap.file == NULL)
		return (SUCCESS);
	initialize_parse_vars(parse);
	if (get_map(parse, parse->imap.file) == 1)
		return (free_double_array(&parse->imap.file), 0);
	if (check_map_ifvalid(parse, parse->map) == FAILURE)
		return (free_parser(parse), 0); 
	if (check_texture(parse) == FAILURE)
		return (free_parser(parse), 0);
	duplicate_parse(parse);
	return (1);
}
