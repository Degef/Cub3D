#include "../includes/cub3D.h"

int endgame(void *pa)
{
	t_data *data;

	data = (t_data *)pa;

	mlx_destroy_window(data->mlx.mlx, data->mlx.window);
	free_memory(data->parse);
	exit(0);
}


int move(int key, void *da)
{
	t_data *data;

	data = (t_data *)da;
	if (key == 53)
		endgame(data);
	return (0);
}

int start_game(t_data *data)
{
	data->mlx.mlx = mlx_init();
	data->mlx.window = mlx_new_window(data->mlx.mlx, 800, 600, "Simple Window");

	mlx_hook(data->mlx.window, 2, 0, &move, data);
	mlx_hook(data->mlx.window, 17, 1L << 17, &endgame, data);
    mlx_loop(data->mlx.mlx);
	return (0);
}
