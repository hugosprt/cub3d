#include "../../includes/cub.h"

void	free_magic(t_game *g)
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
	while (g->tab2[i] != NULL)
	{
		free(g->tab2[i]);
		i++;
	}
	free(g->tab2);
	i = 0;
	while (g->tab3[i] != NULL)
	{
		free(g->tab3[i]);
		i++;
	}
	free(g->tab3);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_help(char *str, char *compas, char *compas2)
{
	free(str);
	free(compas2);
	free(compas);
}

void	leave(t_game *game, char *str, char *compas, char *compas2)
{
	free(str);
	free(compas2);
	free(compas);
	throw_error5(game);
}

void	fail_finish(t_game *g)
{
	free_magic(g);
	free(g->no_texture);
	free(g->so_texture);
	free(g->we_texture);
	free(g->ea_texture);
	free(g->floor_rgb);
	free(g->ceiling_rgb);
	free(g->p);
}
