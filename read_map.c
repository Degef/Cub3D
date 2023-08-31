#include "./includes/cub3D.h"

void realloc_map(t_parse *parse)
{
	char** temp;
	int		i;

    parse->num_lines++;
	temp = ft_calloc(parse->num_lines + 1, sizeof(char*));
	i = -1;
	while (++i < parse->num_lines - 1)
        temp[i] = ft_strdup(parse->text[i]);
    temp[parse->num_lines - 1] = NULL;
    free_double_array(&parse->text, parse->num_lines - 1);
    parse->text = temp;
}

char *substitute_tabs(char **line, char **new_line, int len, int j)
{
	int i;
	int k;

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

void handle_tab(char **line, int i, int len, int tab_count)
{
	int new_len;
	char *new_line;

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

int read_map(t_parse *parse, const char* file_name)
{
    int fd = open(file_name, O_RDONLY);
    if (fd < 0) {
        printf("Error! couldn't open file %s\n", file_name);
        return 0;
    }
    parse->num_lines = 0;
	parse->text = ft_calloc(1, sizeof(char *));
    char* line = NULL;

    while (get_next_line(fd, &line))
	{
        realloc_map((parse));
		handle_tab(&line, -1, 0, 0);
		// printf("%s", line);
        parse->text[parse->num_lines - 1] = ft_substr(line, 0, ft_strlen(line) - 1);
        free(line);
    }
    close(fd);
	int i = -1;
	while (++i < parse->num_lines - 1)
		printf("%s\n", parse->text[i]);
    return 1;
}