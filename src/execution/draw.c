/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Degef <dsium@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 19:13:14 by Degef             #+#    #+#             */
/*   Updated: 2023/10/06 20:53:34 by Degef            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	is_ceiling(unsigned int **buffer, int i, int k)
{
	if (i == 0)
		return (1);
	while (--i > -1)
	{
		if (buffer[i][k] != 0)
			return (0);
	}
	return (1);
}

int	is_floor(unsigned int **buffer, int i, int k)
{
	if (i == 0)
		return (1);
	while (++i < WIN_H)
	{
		if (buffer[i][k] != 0)
			return (0);
	}
	return (1);
}

void	update_image(t_data *data, int j, int i)
{
	if (is_ceiling(data->buffer, i, j))
		data->image.addr[i * WIN_W + j] = data->parse->ceil_color;
	else if (is_floor(data->buffer, i, j))
		data->image.addr[i * WIN_W + j] = data->parse->floor_color;
	else
		data->image.addr[i * WIN_W + j] = data->buffer[i][j];
	if (((i > WIN_H / 2 - 8 && i < WIN_H / 2 - 3)
			|| (i > WIN_H / 2 + 3 && i < WIN_H / 2 + 8))
		&& j == WIN_W / 2)
		data->image.addr[i * WIN_W + j] = 0x00FF00;
	if (((j > WIN_W / 2 - 8 && j < WIN_W / 2 - 3)
			|| (j > WIN_W / 2 + 3 && j < WIN_W / 2 + 8))
		&& i == WIN_H / 2)
		data->image.addr[i * WIN_W + j] = 0x00FF00;
}

int	put_pixels(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (++i < WIN_H)
	{
		j = -1;
		while (++j < WIN_W)
			update_image(data, j, i);
	}
	data->image.addr[WIN_H / 2 * WIN_W + WIN_W / 2] = 0x00FF00;
	return (0);
}
