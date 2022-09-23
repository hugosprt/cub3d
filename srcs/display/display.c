#include "../../includes/cub.h"

void	init_img(t_game *g, char **tab)
{
	int		height;
	int		width;
	t_img	size;

	height = ft_strlen(tab[0]) * 128;
	width = g->size * 128;
	g->mlx = mlx_init();
	g->win = mlx_new_window(g->mlx, height, width, "CUB3D");
	g->txtr[PLAYER].img = mlx_xpm_file_to_image(g->mlx,
			"./images/mur2.xpm", &size.img_width, &size.img_height);
	g->txtr[WALL].img = mlx_xpm_file_to_image(g->mlx,
			"./images/mur.xpm", &size.img_width, &size.img_height);
	g->txtr[WALL2].img = mlx_xpm_file_to_image(g->mlx,
			"./images/mur2.xpm", &size.img_width, &size.img_height);

}

void	finish(t_game *g, char **tab)
{
	int	i;

	(void) tab;
	i = 0;
	while (g->tab[i] != NULL)
	{
		free(g->tab[i]);
		i++;
	}
	free(g->tab);
	i = 0;
	while (i < 3)
	{
		mlx_destroy_image(g->mlx, g->txtr[i].img);
		i++;
	}
	mlx_destroy_window(g->mlx, g->win);
	mlx_destroy_display(g->mlx);
	free(g->mlx);
	free(g);
	exit(EXIT_SUCCESS);
}

static void	print_txtr(t_game *root, int x, int y, int type)
{
	mlx_put_image_to_window(root->mlx, root->win, root->txtr[type].img, x, y);
}

void	print_tiles(t_game *a, char **tab)
{
	a->y = -1;
	while (tab[++a->y])
	{
		a->x = -1;
		while (tab[a->y][++a->x])
		{
			if (tab[a->y][a->x] == '1')
				print_txtr(a, a->x * 128, a->y * 128, WALL + (a->step % 4));
			if (tab[a->y][a->x] == '0')
				print_txtr(a, a->x * 128,
					a->y * 128, WALL + ((a->step + 1) % 4));
			if (tab[a->y][a->x] == 'P')
			{
				print_txtr(a, a->x * 128, a->y * 128, PLAYER);
				a->yy = a->y;
				a->xx = a->x;
			}
		}
	}
	a->x = a->xx;
	a->y = a->yy;
}
