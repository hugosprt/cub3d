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
				g->map[g->y][g->x] = '0';
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
	g->x_mmax = ft_strlen(g->map[0]);
	g->y_mmax = ft_tablen(g->map);
}

void	init_rays(t_game *g)
{
	int		id;
	t_ray	*ray;

	id = 0;
	ray = malloc(sizeof(t_ray) * 1);
	g->ray = ray;
	ray->id = id;
	while (id < g->wwidth)
	{
		ray->next = malloc(sizeof(t_ray) * 1);
		ray = ray->next;
		ray->id = id;
		id++;
	}
	ray->next = NULL;
}

void	init_game(t_game *g, char *file)
{
	g->wwidth = 1200;
	g->wheight = 800;
	init_rays(g);
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
	g->truc_parse = 0;
	g->texture = 0;
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
	g->p = malloc(sizeof(t_player));
	g->p->x = 0;
	g->p->y = 0;
	g->p->a = 0;
	g->p->i = 0;
	meke_tab(g);
}

void	finish(t_game *g)
{
	mlx_destroy_image(g->mlx, g->t_n->mlx_xmp);
	mlx_destroy_image(g->mlx, g->t_s->mlx_xmp);
	free_magic(g);
	free(g->NO_texture);
	free(g->SO_texture);
	free(g->WE_texture);
	free(g->EA_texture);
	free(g->floor_rgb);
	free(g->ceiling_rgb);
	//mlx_destroy_image(g->mlx, g->t_e->mlx_xmp);
	//mlx_destroy_image(g->mlx, g->t_w->mlx_xmp);
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

void	texture_init(t_game *g, t_texture *texture, char *path_texture)
{
	int	t;
	int	t1;

	t = 64;
	ft_printf("path to texture %s\n", path_texture);
	texture->mlx_xmp = mlx_xpm_file_to_image(g->mlx, path_texture, &t, &t1);
	if (t != 64 || t1 != 64)
	{
		ft_printf("Stop this right now and give me good texture\n");
		exit (69);
	}
	if (!texture->mlx_xmp)
	{
		ft_printf("Stop this right now and give me good texture\n");
		exit (69);
	}
	texture->adr = mlx_get_data_addr(texture->mlx_xmp, &texture->bitsz,
			&texture->lsz, &texture->endi);
}

void	init_textures(t_game *g)
{
	g->t_n = malloc(sizeof(t_texture *) * 1);
	g->t_s = malloc(sizeof(t_texture *) * 1);
	g->t_e = malloc(sizeof(t_texture *) * 1);
	g->t_w = malloc(sizeof(t_texture *) * 1);
	texture_init(g, g->t_n, g->NO_texture);
	texture_init(g, g->t_s, g->SO_texture);
	//texture_init(g, g->t_e, g->NO_texture);
	//texture_init(g, g->t_w, g->NO_texture);
}

int	main(int ac, char **av)
{
t_game	*game;

	(void) ac;
	(void) av;
	game = malloc((sizeof (t_game)));
	init_game(game, "map2.cub");
	main_parsing(game);
	//print_map2(game);
	init_player_position(game, game->map);
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
