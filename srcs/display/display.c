#include "../../includes/cub.h"

void	init_img(t_game *g, char **tab)
{
	int		height;
	int		width;
	t_img	size;

	height = ft_strlen(tab[0]) * 128;
	width = g->size * 128;
	g->win = mlx_new_window(g->mlx, height, width, "CUB3D");
	g->p = malloc(sizeof(t_player));
	g->txtr[WALL].img = mlx_xpm_file_to_image(g->mlx,
			"./images/mur.xpm", &size.img_width, &size.img_height);
	g->txtr[WALL2].img = mlx_xpm_file_to_image(g->mlx,
			"./images/mur2.xpm", &size.img_width, &size.img_height);

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
	mlx_destroy_image(g->mlx, g->txtr[0].img);
	mlx_destroy_image(g->mlx, g->txtr[1].img);
	mlx_destroy_window(g->mlx, g->win);
	mlx_destroy_display(g->mlx);
	free(g->p);
	free(g->mlx);
	free(g);
	ft_printf("hop c fini\n");
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
				print_txtr(a, a->x * 128, a->y * 128, WALL2);
			if (tab[a->y][a->x] == '0')
				print_txtr(a, a->x * 128,
					a->y * 128, WALL);
			if (tab[a->y][a->x] == 'P')
			{
				tab[a->y][a->x] = '0';
				a->p->x = (a->x * 128) + 64;
				a->p->y = (a->y * 128) + 64;
				print_txtr(a, a->x * 128, a->y * 128, WALL);
				a->yy = a->y;
				a->xx = a->x;
			}
		}
	}
	mlx_pixel_put(a->mlx, a->win, a->p->x, a->p->y, 0xff0000);
	mlx_pixel_put(a->mlx, a->win, a->p->x + 1, a->p->y, 0xff0000);
	mlx_pixel_put(a->mlx, a->win, a->p->x, a->p->y + 1, 0xff0000);
	mlx_pixel_put(a->mlx, a->win, a->p->x, a->p->y + 1, 0xff0000);
	a->x = a->xx;
	a->y = a->yy;
}
