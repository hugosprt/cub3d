#include "../includes/cub.h"


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
				g->tab3[g->y][g->x] = '0';
			}
		}
	}
}

void	init_game(t_game *g, char *file)
{
	
	g->x = 0;
	g->NO_texture = NULL;
	g->SO_texture = NULL;
	g->EA_texture = NULL;
	g->WE_texture = NULL;
	g->floor_rgb = NULL;
	g->ceiling_rgb = NULL;
	g->tab = NULL;
	g->tab2 = NULL;
	g->tab3 = NULL;
	g-> truc_parse = 0;
	g->texture =0;
	g->y = 0;
	g->is_player = 'H';
	g->is_valid = 1;
	g->fd = open(file, O_RDONLY);
	g->ts = 64;
	g->rotation_speed = 1;
	g->step_speed = 4;
	g->side = 0;
	g->step = 0;
	g->turn = 0;
	g->fov = 60 * (PI / 180);
	g->wwidth = 1200;
	g->wheight = 800;
	g->p = malloc(sizeof(t_player));
	g->p->x = 0;
	g->p->y = 0;
	g->p->a = 0;
	
}

void	finish(t_game *g)
{
	int	i;

	i = 0;
	free_magic(g);
	free(g->NO_texture);
	free(g->SO_texture);
	free(g->WE_texture);
	free(g->EA_texture);
	free(g->floor_rgb);
	free(g->ceiling_rgb);
	i = 0;
	mlx_destroy_window(g->mlx, g->win);
	mlx_destroy_display(g->mlx);
	free(g->p);
	free(g->mlx);
	free(g);
	ft_printf("hop c fini\n");
	exit(EXIT_SUCCESS);
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

void print_map2(t_game *game)
{
	int i = 0;
	int j = 0;
	while (game->tab3[j])
	{
		i = 0;
		while (game->tab3[j][i])
		{
			printf("%c", game->tab3[j][i]);
			i++;
		}
		printf("\n");
		j++;
	}
}

int	main(int ac, char **av)
{
t_game	*game;

	(void) ac;
	(void) av;
	game = malloc((sizeof (t_game)));
	init_game(game, av[1]);
	main_parsing(game);
	//print_map2(game);
	init_player_position(game, game->tab3);
	if (ac != 2)
		parse_error();
	game->mlx = mlx_init();
	if (game->mlx == NULL)
		parse_error();
	game->win = mlx_new_window(game->mlx, game->wwidth, game->wheight, "CUB3D");
	mlx_hook(game->win, 02, 1l << 0, key_pressed, game);
	mlx_hook(game->win, 3, 1L << 1, key_released, game);
	mlx_loop_hook(game->mlx, render, game);
	mlx_hook(game->win, 17, 1L << 5, mlx_loop_end, game->mlx);
	mlx_loop(game->mlx);
	finish(game);
	return (0);
} 
