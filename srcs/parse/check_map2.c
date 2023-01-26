#include "../../includes/cub.h"

void	is_collunm_top(t_game *game)
{
	int	i;
	int	j;
	int	size;

	size = find_longer_line(game->tab3);
	i = 0;
	j = 0;
	while (j != size)
	{
		i = 0;
		while (game->tab3[i][j] != '1')
		{
			if (game->tab3[i][j] != ' ')
				throw_error4(game);
			i++;
		}
		j++;
	}
}

void	is_collunm_bot(t_game *game)
{
	int	i;
	int	j;
	int	size;
	int	s2;

	size = find_longer_line(game->tab3);
	s2 = find_longer_collum(game->tab3);
	i = 0;
	j = 0;
	while (j != size)
	{
		i = 1;
		while (game->tab3[s2 - i][j] != '1')
		{
			if (game->tab3[s2 - i][j] != ' ')
				throw_error4(game);
			i++;
		}
		j++;
	}
}

void	is_line_left(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (game->tab3[j])
	{
		i = 0;
		while (game->tab3[j][i] != '1')
		{
			if (game->tab3[j][i] != ' ')
				throw_error4(game);
			i++;
		}
		j++;
	}
}

void	is_line_right(t_game *game)
{
	int	i;
	int	j;
	int	size;

	size = find_longer_line(game->tab3);
	i = 0;
	j = 0;
	while (game->tab3[j])
	{
		i = 1;
		while (game->tab3[j][size - i] != '1')
		{
			if (game->tab3[j][size - i] != ' ')
				throw_error4(game);
			i++;
		}
		j++;
	}
}
