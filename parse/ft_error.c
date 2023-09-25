/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aandom <aandom@student.abudhabi42.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 19:26:36 by aandom            #+#    #+#             */
/*   Updated: 2023/09/25 12:10:50 by aandom           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	check_front(char **map, int j, int i)
{
	while (i >= 0)
	{
		if (map[j][i] == '1')
			return (1);
		i--;
	}
	return (0);
}

int	print_err(char *info, char *str, int code)
{
	ft_putstr_fd("cub3D: Error", 2);
	if (info)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(info, 2);
	}
	if (str)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(str, 2);
	}
	ft_putstr_fd("\n", 2);
	return (code);
}

void	void_free_arr(void **str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	if (str)
	{
		free(str);
		str = NULL;
	}
}

int	print_err_val(int detail, char *str, int code)
{
	ft_putstr_fd("cub3D: Error: ", 2);
	ft_putnbr_fd(detail, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	return (code);
}

void	free_parser(t_parse *parse)
{
	free_double_array(&parse->imap.file);
	if (parse->map != NULL)
		free_double_array(&parse->map);
	if (parse->no_text != NULL)
		free(parse->no_text);
	if (parse->so_text != NULL)
		free(parse->so_text);
	if (parse->we_text != NULL)
		free(parse->we_text);
	if (parse->ea_text != NULL)
		free(parse->ea_text);
	if (parse->ceiling != NULL)
		free(parse->ceiling);
	if (parse->floor != NULL)
		free(parse->floor);
}
