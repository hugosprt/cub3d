#include "../includes/cub.h"

static char	**meke_tab(void)
{
	char	**tab;

	tab = malloc(sizeof(char *) * 4);
	tab[0] = ft_strdup("11111");
	tab[1] = ft_strdup("10P01");
	tab[2] = ft_strdup("11111");
	tab[3] = NULL;
	return (tab);
}

static int	ft_truc(int keycode, t_game *g)
{
	if (keycode == 115)
		move_up(g, -1);
	if (keycode == 119)
		move_up(g, 1);
	if (keycode == 100)
		move_right(g, 1);
	if (keycode == 97)
		move_right(g, -1);
	if (keycode == 65361)
		rotate(g, -1);
	if (keycode == 65363)
		rotate(g, 1);
	if (keycode == 65307)
		finish(g);
	return (0);
}

static int	ft_truc2(t_game *g)
{
	ft_truc(65307, g);
	return (0);
}

int	main(int ac, char **av)
{
	t_game	*game;

	(void) ac;
	(void) av;
	game = malloc((sizeof (t_game)));
	if (ac != 2)
		parse_error();
	game->mlx = mlx_init();
	if (game->mlx == NULL)
		parse_error();
	parse(av[1], game);
	game->tab = meke_tab();
	init_img(game, game->tab);
	mlx_hook(game->win, 02, 1l << 0, ft_truc, game);
	mlx_hook(game->win, 17, 1L << 5, ft_truc2, game);
	print_tiles(game, game->tab);
	mlx_loop(game->mlx);
	return (0);
}
