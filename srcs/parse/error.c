#include "../../includes/cub.h"

void	throw_error(t_game *game, char *tab)
{
	ft_printf("Error, can't open map\n");
	free(tab);
	free(game);
	exit(EXIT_FAILURE);
}

void	throw_error2(t_game *game, char *tab)
{
	ft_printf("error no map\n");
	free(tab);
	free(game);
	exit(EXIT_FAILURE);
}

void	throw_error5(t_game *g)
{
	int	i;

	i = 0;
	while (g->tab[i] != NULL)
	{
		free(g->tab[i]);
		i++;
	}
	if (g->ea_texture != NULL)
		free(g->ea_texture);
	if (g->we_texture != NULL)
		free(g->we_texture);
	if (g->no_texture != NULL)
		free(g->no_texture);
	if (g->so_texture != NULL)
		free(g->so_texture);
	if (g->ceiling_rgb != NULL)
		free(g->ceiling_rgb);
	if (g->floor_rgb != NULL)
		free(g->floor_rgb);
	free(g->tab);
	i = 0;
	while (g->tab2[i] != NULL)
	{
		free(g->tab2[i]);
		i++;
	}
	free(g->tab2);
	free(g->p);
	free(g);
	ft_printf("error map5\n");
	exit(EXIT_FAILURE);
}

void	throw_error3(t_game *g, char *tab)
{
	int	i;

	i = 0;
	(void) tab;
	while (g->tab[i] != NULL)
	{
		free(g->tab[i]);
		i++;
	}
	free(g->tab);
	i = 0;
	while (g->tab2[i] != NULL)
	{
		free(g->tab2[i]);
		i++;
	}
	free(g->tab2);
	free(g->p);
	free(g);
	ft_printf("error map4\n");
	exit(EXIT_FAILURE);
}

void	throw_error4(t_game *game)
{
	ft_printf("error map2\n");
	fail_finish(game);
	free(game);
	exit(EXIT_FAILURE);
}

void	throw_error66(t_game *game)
{
	ft_printf("too many players\n");
	free(game);
	exit(EXIT_FAILURE);
}
