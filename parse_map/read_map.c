/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Degef <dsium@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 15:30:27 by Degef             #+#    #+#             */
/*   Updated: 2023/09/20 15:38:16 by Degef            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

char	*substitute_tabs(char **line, char **new_line, int len, int j)
{
	int	i;
	int	k;

	i = -1;
	k = 0;
	while (++i < len)
	{
		if ((*line)[i] == '\t')
		{
			while (++k <= 4)
				(*new_line)[j++] = ' ';
			k = 0;
		}
		else
			(*new_line)[j++] = (*line)[i];
	}
	free(*line);
	return (*new_line);
}

void	handle_tab(char **line, int i, int len, int tab_count)
{
	int		new_len;
	char	*new_line;

	len = ft_strlen(*line);
	while (++i < len)
		if ((*line)[i] == '\t')
			tab_count++;
	if (tab_count == 0)
		return ;
	new_len = len + (tab_count * 3);
	new_line = ft_calloc(new_len + 1, sizeof(char));
	*line = substitute_tabs(line, &new_line, len, 0);
}

int	count_lines(const char *file_name)
{
	int		i;
	int		fd;
	char	*line;

	i = 0;
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return (printf("Error! couldn't open file %s\n", file_name), 0);
	line = NULL;
	while (get_next_line(fd, &line))
		i++;
	close(fd);
	return (i);
}

int	read_map(t_parse *parse, const char *file_name)
{
	int		fd;
	char	*line;
	int		i;

	i = -1;
	parse->num_lines = count_lines(file_name);
	if (parse->num_lines <= 0)
		return (0);
	parse->text = ft_calloc(parse->num_lines + 1, sizeof(char *));
	fd = open(file_name, O_RDONLY);
	while (get_next_line(fd, &line))
	{
		handle_tab(&line, -1, 0, 0);
		if (line[0] == '\n')
			parse->text[++i] = ft_strdup(line);
		else if (line[ft_strlen(line) - 1] == '\n')
			parse->text[++i] = ft_substr(line, 0, ft_strlen(line) - 1);
		else
			parse->text[++i] = ft_strdup(line);
		free(line);
	}
	close(fd);
	return (1);
}
	// i = -1;
	// while (parse->text[++i])
	// 	printf("%s\n", parse->text[i]);
