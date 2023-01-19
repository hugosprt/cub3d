#include "../includes/cub.h"

int	ft_tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

int	where_is_player_facing(char direction)
{
	if (direction == 'N')
		return (90);
	if (direction == 'S')
		return (270);
	if (direction == 'W')
		return (180);
	if (direction == 'E')
		return (0);
	return (90);
}

void	init_player_position(t_game *g, char **tab)
{
	g->y = -1;
	while (tab[++g->y])
	{
		g->x = -1;
		while (tab[g->y][++g->x])
		{
			if (tab[g->y][g->x] == 'N' || tab[g->y][g->x] == 'S' ||
				tab[g->y][g->x] == 'E' || tab[g->y][g->x] == 'W')
			{
				g->p->x = (g->x * g->ts) + (g->ts / 2);
				g->p->y = (g->y * g->ts) + (g->ts / 2);
				g->p->a = where_is_player_facing(tab[g->y][g->x]);
				g->rad = (g->p->a * (PI / 180));
				tab[g->y][g->x] = '0';
			}
		}
	}
}

void	init_game(t_game *g)
{
	g->ts = 64;
	g->rotation_speed = 1;
	g->step_speed = 1;
	g->side = 0;
	g->step = 0;
	g->turn = 0;
	g->sky_color = 0x0000FF00;
	g->ground_color = 0x000000FF;
	g->fov = 60 * (PI / 180);
	g->wwidth = 1200;
	g->wheight = 800;
	g->p = malloc(sizeof(t_player));
	g->p->x = 0;
	g->p->y = 0;
	g->p->a = 0;
	init_player_position(g, g->tab);
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

void	meke_tab(t_game *g)
{

	g->tab = malloc(sizeof(char *) * 12);
	g->tab[0] = ft_strdup("111111111111111");
	g->tab[1] = ft_strdup("100000000110001");
	g->tab[2] = ft_strdup("111100000000001");
	g->tab[3] = ft_strdup("100000000011001");
	g->tab[4] = ft_strdup("101111110000001");
	g->tab[5] = ft_strdup("100110000000001");
	g->tab[6] = ft_strdup("1000000N0000111");
	g->tab[7] = ft_strdup("100000000011101");
	g->tab[8] = ft_strdup("111100000000001");
	g->tab[9] = ft_strdup("100000000000101");
	g->tab[10] = ft_strdup("111111111111111");
	g->tab[11] = NULL;
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
	meke_tab(game);
	init_game(game);
	if (ac != 2)
		parse_error();
	game->mlx = mlx_init();
	if (game->mlx == NULL)
		parse_error();
	//parse(av[1], game);
	game->win = mlx_new_window(game->mlx, game->wwidth, game->wheight, "CUB3D");
	mlx_hook(game->win, 02, 1l << 0, key_pressed, game);
	mlx_hook(game->win, 3, 1L << 1, key_released, game);
	mlx_loop_hook(game->mlx, render, game);
	mlx_hook(game->win, 17, 1L << 5, mlx_loop_end, game->mlx);
	mlx_loop(game->mlx);
	finish(game);
	return (0);
}
