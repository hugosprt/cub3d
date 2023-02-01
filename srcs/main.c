#include "../includes/cub.h"

void	init_game(t_game *g, char *file)
{
	g->wwidth = 1200;
	g->wheight = 800;
	g->truc = 0;
	g->x = 0;
	g->y = 0;
	g->no_texture = NULL;
	g->so_texture = NULL;
	g->ea_texture = NULL;
	g->we_texture = NULL;
	g->floor_rgb = NULL;
	g->ceiling_rgb = NULL;
	g->tab = NULL;
	g->tab2 = NULL;
	g->tab3 = NULL;
	g->truc_parse = 0;
	g->texture = 0;
	g->is_player = 'H';
	g->is_valid = 1;
	g->fd = open(file, O_RDONLY);
	g->ts = 64;
	init_player_param(g);
}

void	finish(t_game *g)
{
	destroy_images_texture(g);
	free_magic(g);
	free(g->no_texture);
	free(g->so_texture);
	free(g->we_texture);
	free(g->ea_texture);
	free(g->floor_rgb);
	free(g->ceiling_rgb);
	if (g->win != NULL)
	{
		mlx_destroy_window(g->mlx, g->win);
		ft_printf("hop c fini\n");
	}
	mlx_destroy_display(g->mlx);
	free(g->p);
	free(g->mlx);
	free(g);
	exit(EXIT_SUCCESS);
}

int	main(int ac, char **av)
{
	t_game	*game;

	(void) av;
	game = malloc((sizeof (t_game)));
	init_game(game, av[1]);
	main_parsing(game);
	init_player_position(game, game->tab3);
	if (ac != 2)
		parse_error();
	game->mlx = mlx_init();
	if (game->mlx == NULL)
		parse_error();
	init_textures(game);
	game->win = mlx_new_window(game->mlx, game->wwidth, game->wheight, "CUB3D");
	mlx_hook(game->win, 02, 1l << 0, key_pressed, game);
	mlx_hook(game->win, 3, 1L << 1, key_released, game);
	mlx_loop_hook(game->mlx, render, game);
	mlx_hook(game->win, 17, 1L << 5, mlx_loop_end, game->mlx);
	mlx_loop(game->mlx);
	finish(game);
	return (0);
}
