/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Degef <dsium@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 19:26:36 by aandom            #+#    #+#             */
/*   Updated: 2023/09/23 18:06:03 by Degef            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

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
	free_double_array(&parse->map);
	free(parse->no_text);
	free(parse->so_text);
	free(parse->we_text);
	free(parse->ea_text);
	free(parse->ceiling);
	free(parse->floor);
}
