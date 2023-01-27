#include "../includes/cub.h"


float	where_is_player_facing(char direction)
{
	if (direction == 'N')
		return (PI / 2);
	if (direction == 'S')
		return (PI);
	if (direction == 'W')
		return ((3 * PI) / 2);
	if (direction == 'E')
		return (2 * PI);
	return (PI / 2);
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
				g->rad = where_is_player_facing(tab[g->y][g->x]);
				g->tab3[g->y][g->x] = '0';
			}
		}
	}
	g->x_max = ft_strlen(tab[0]) * g->ts;
	g->y_max = ft_tablen(tab) * g->ts;
}

void	meke_tab(t_game *g)
{
	g->map = malloc(sizeof(char *) * 12);
	g->map[0] = ft_strdup("111111111111111");
	g->map[1] = ft_strdup("100000000110001");
	g->map[2] = ft_strdup("111100000000001");
	g->map[3] = ft_strdup("100000000011001");
	g->map[4] = ft_strdup("101111110000001");
	g->map[5] = ft_strdup("100110000000001");
	g->map[6] = ft_strdup("1000000N0000111");
	g->map[7] = ft_strdup("100000000011101");
	g->map[8] = ft_strdup("111100000000001");
	g->map[9] = ft_strdup("100000000000101");
	g->map[10] = ft_strdup("111111111111111");
	g->map[11] = NULL;
	
}

void	init_game(t_game *g, char *file)
{
	g->wwidth = 1200;
	g->wheight = 800;
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
	g->rotation_speed = PI / 90;
	g->step_speed = 4;
	g->side_speed = 2;
	g->side = 0;
	g->step = 0;
	g->turn = 0;
	g->fov = 60 * (PI / 180);
	g->p = malloc(sizeof(t_player));
	g->p->x = 0;
	g->p->y = 0;
	g->p->i = 0;
	
	//meke_tab(g);
}

void	finish(t_game *g)
{
	mlx_destroy_image(g->mlx, g->t_n);
	mlx_destroy_image(g->mlx, g->t_s);
	mlx_destroy_image(g->mlx, g->t_e);
	mlx_destroy_image(g->mlx, g->t_w);
	free_magic(g);
	free(g->no_texture);
	free(g->so_texture);
	free(g->we_texture);
	free(g->ea_texture);
	free(g->floor_rgb);
	free(g->ceiling_rgb);
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

void print_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		ft_printf("%s\n", tab[i]);
		i++;
	}
}

void	*texture_init(t_game *g, char *path_texture)
{
	int		t;
	int		t1;
	void	*txt;

	t = 64;
	txt = mlx_xpm_file_to_image(g->mlx, path_texture, &t, &t1);
	if (t != 64 || t1 != 64)
	{
		ft_printf("Stop this right now and give me good texture\n");
		exit (69);
	}
	if (!txt)
	{
		ft_printf("Stop this right now and give me good texture\n");
		exit (69);
	}
	return (txt);
}

void	init_textures(t_game *g)
{
	g->t_n = texture_init(g, g->no_texture);
	g->t_s = texture_init(g, g->so_texture);
	g->t_e = texture_init(g, g->ea_texture);
	g->t_w = texture_init(g, g->we_texture);
}

int	main(int ac, char **av)
{
t_game	*game;

	(void) ac;
	(void) av;
	game = malloc((sizeof (t_game)));
	init_game(game, "map2.cub");
	main_parsing(game);
	game->x_mmax = ft_strlen(game->tab3[0]);
	game->y_mmax = ft_tablen(game->tab3) - 1;
	//print_map2(game);
	init_player_position(game, game->tab3);
	//print_tab(game->map);
	if (ac != 2)
		parse_error();
	game->mlx = mlx_init();
	if (game->mlx == NULL)
		parse_error();
	game->win = mlx_new_window(game->mlx, game->wwidth, game->wheight, "CUB3D");
	init_textures(game);
	mlx_hook(game->win, 02, 1l << 0, key_pressed, game);
	mlx_hook(game->win, 3, 1L << 1, key_released, game);
	mlx_loop_hook(game->mlx, render, game);
	mlx_hook(game->win, 17, 1L << 5, mlx_loop_end, game->mlx);
	mlx_loop(game->mlx);
	finish(game);
	return (0);
}
