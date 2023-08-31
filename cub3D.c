#include "../includes/cub3D.h"

int		is_cubfile(char *file)
{
	int i;

	i = ft_strlen(file);
	if (file[i - 4] != '.' || (file[i - 3] != 'c' || (file[i - 2] != 'u') || (file[i - 1] != 'b')))
		return (0);
	return (1);
}

void realloc_map(t_data **data)
{
	char** temp;
	int		i;

    (*data)->num_lines++;
	temp = (char**)malloc((*data)->num_lines * sizeof(char*));
	i = -1;
	while (++i < (*data)->num_lines - 1)
        temp[i] = ft_strdup((*data)->map[i]);
    temp[(*data)->num_lines - 1] = NULL;
    free_double_array(&(*data)->map, (*data)->num_lines - 1);
    (*data)->map = temp;
}

int read_map(t_data **data, const char* file_name) {
    int fd = open(file_name, O_RDONLY);
    if (fd < 0) {
        printf("Error! couldn't open file %s\n", file_name);
        return 0;
    }

    (*data)->num_lines = 0;
	(*data)->map = ft_calloc(1, sizeof(char *));
    char* line = NULL;

    while (get_next_line(fd, &line))
	{
		// printf("line %s\n", line);
        realloc_map((data));
        (*data)->map[(*data)->num_lines - 1] = ft_strdup(line);
        free(line);
    }
    close(fd);
	// int i = -1;
	// while (++i < (*data)->num_lines - 1)
	// 	printf("%s", (*data)->map[i]);
    return 1;
}


int main(int argc, char **argv)
{
	t_data	*data;
	if (argc < 2 || argc > 2)
		printf("Error! Wrong input. Usage (./Cub3d ./map/map.cub)\n");
	if (!is_cubfile(argv[1]))
		return (printf("Error! map is not .cub file\n"), 1);
	data = malloc(sizeof(t_data));
	if (!read_map(&data, argv[1]))
		return (1);
	
	free_double_array(&data->map, data->num_lines);
	free(data);
	return (0);
}
