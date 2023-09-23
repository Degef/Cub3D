/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_check.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandom <aandom@student.abudhabi42.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 19:05:03 by aandom            #+#    #+#             */
/*   Updated: 2023/09/23 15:51:11 by aandom           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static int	check_buttom(char **map, int i, int j)
{
	while (map[i - 1][j])
	{
		if (map[i - 1][j] != '1')
			return (FAILURE);
		j++;
	}
	return (SUCCESS);
}

static int	check_top(char **map, int i, int j)
{
	while (map[i + 1][j])
	{
		if (map[i + 1][j] != '1')
			return (FAILURE);
		j++;
	}
	return (SUCCESS);
}

static int	check_top_or_bottom(char **map_tab, int i, int j)
{
	if (!map_tab || !map_tab[i] || !map_tab[i][j])
		return (FAILURE);
	while (map_tab[i][j] == ' ' || map_tab[i][j] == '\t'
	|| map_tab[i][j] == '\r' || map_tab[i][j] == '\v'
	|| map_tab[i][j] == '\f')
		j++;
	while (map_tab[i][j])
	{
		if (map_tab[i][j] != '1')
		{
			printf("failure is [%d][%d] = %ul\n", i, j, (unsigned char)map_tab[i][j] );
			return (FAILURE);
		}
		j++;
	}
	printf("not failure\n");
	if (i != 0)
		return (check_buttom(map_tab, i, j));
	return (check_top(map_tab, i, j));
	// return (SUCCESS);
}

int	check_map_sides(t_imap *map, char **map_tab)
{
	int	i;
	int	j;

	if (check_top_or_bottom(map_tab, 0, 0) == FAILURE)
		return (FAILURE);
	i = 1;
	while (i < (map->height - 1))
	{
		j = ft_strlen(map_tab[i]) - 1;
		if (map_tab[i][j] != '1')
		{
			return (FAILURE);
		}
		i++;
	}
	if (check_top_or_bottom(map_tab, i, 0) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

int	check_map_ifvalid(t_parse *parse, char **map)
{
	if (!parse->map)
		return (print_err(parse->imap.path, "ERR_MAP_MISSING", FAILURE));
	if (check_map_sides(&parse->imap, map) == FAILURE)
		return (print_err(parse->imap.path, "ERR_MAP_NO_WALLS", FAILURE));
	if (parse->imap.height < 3)
		return (print_err(parse->imap.path, "ERR_MAP_TOO_SMALL", FAILURE));
	if (check_map_elements(parse, map) == FAILURE)
		return (FAILURE);
	if (check_map_is_at_the_end(&parse->imap) == FAILURE)
		return (print_err(parse->imap.path, "ERR_MAP_LAST", FAILURE));
	return (SUCCESS);
}
