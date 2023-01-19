#include "../includes/cub.h"

static int	ft_tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

void	init_game(t_game *g)
{
	g->ts = 64;
	g->wwidth = ft_strlen(g->tab[0]) * g->ts;
	g->wheight = ft_tablen(g->tab) * g->ts;
	g->rotation_speed = 1;
	g->step_speed = 1;
	g->side = 0;
	g->step = 0;
	g->turn = 0;
	g->win = mlx_new_window(g->mlx, g->wwidth, g->wheight, "CUB3D");
	g->p = malloc(sizeof(t_player));
	g->p->x = 0;
	g->p->y = 0;
	g->p->a = 0;
}

void	finish(t_game *g)
{
	int	i;

	i = 0;
	while (g->tab[i] != NULL)
	{
		free(g->tab[i]);
		i++;
	}
	free(g->tab);
	i = 0;
	mlx_destroy_window(g->mlx, g->win);
	mlx_destroy_display(g->mlx);
	free(g->p);
	free(g->mlx);
	free(g);
	ft_printf("hop c fini\n");
	exit(EXIT_SUCCESS);
}

static char	**meke_tab(void)
{
	char	**tab;

	tab = malloc(sizeof(char *) * 12);
	tab[0] = ft_strdup("111111111111111");
	tab[1] = ft_strdup("100000000110001");
	tab[2] = ft_strdup("111100000000001");
	tab[3] = ft_strdup("100000000011001");
	tab[4] = ft_strdup("101111110000001");
	tab[5] = ft_strdup("100110000000001");
	tab[6] = ft_strdup("1000000N0000111");
	tab[7] = ft_strdup("100000000011101");
	tab[8] = ft_strdup("111100000000001");
	tab[9] = ft_strdup("100000000000101");
	tab[10] = ft_strdup("111111111111111");
	tab[11] = NULL;
	return (tab);
}

static int	key_pressed(int keycode, t_game *game)
{
	if (keycode == 115)
		game->step += 1;
	if (keycode == 119)
		game->step -= 1;
	if (keycode == 100)
		game->side -= 1;
	if (keycode == 97)
		game->side += 1;
	if (keycode == 65361)
		game->turn -= 1;
	if (keycode == 65363)
		game->turn += 1;
	if (keycode == 65307)
		mlx_loop_end(game->mlx);
	return (0);
}

int	key_released(int keycode, t_game *game)
{
	if (keycode == 115)
		game->step = 0;
	if (keycode == 119)
		game->step = 0;
	if (keycode == 100)
		game->side = 0;
	if (keycode == 97)
		game->side = 0;
	if (keycode == 65361)
		game->turn = 0;
	if (keycode == 65363)
		game->turn = 0;
	if (keycode == 65307)
		mlx_loop_end(game->mlx);
	return (0);
}

int	main(int ac, char **av)
{
	t_game	*game;

	(void) ac;
	(void) av;
	game = malloc((sizeof (t_game)));
	game->tab = meke_tab();
	if (ac != 2)
		parse_error();
	game->mlx = mlx_init();
	if (game->mlx == NULL)
		parse_error();
	//parse(av[1], game);
	init_game(game);
	render(game);
	mlx_hook(game->win, 02, 1l << 0, key_pressed, game);
	mlx_hook(game->win, 3, 1L << 1, key_released, game);
	mlx_loop_hook(game->mlx, render, game);
	mlx_hook(game->win, 17, 1L << 5, mlx_loop_end, game->mlx);
	mlx_loop(game->mlx);
	finish(game);
	return (0);
}
