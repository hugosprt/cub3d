/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hspriet <hspriet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 19:59:04 by hspriet           #+#    #+#             */
/*   Updated: 2023/02/01 20:06:42 by hspriet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

int	check_zero(t_game *game, int i, int j)
{
	if (!game->tab3[j][i + 1] || game->tab3[j][i + 1] == ' ')
		return (0);
	if (!game->tab3[j][i - 1] || game->tab3[j][i - 1] == ' ')
		return (0);
	if (!game->tab3[j - 1][i] || game->tab3[j - 1][i] == ' ')
		return (0);
	return (1);
}

void	if_zero(t_game *game, char **tab3)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (tab3[j])
	{
		i = 0;
		while (tab3[j][i])
		{
			if (tab3[j][i] == '0')
			{
				if (!check_zero(game, i, j))
					throw_error4(game);
			}
			i++;
		}
		j++;
	}
}

int	ft_isbinary(char c)
{
	if (c == '1' || c == '0')
		return (1);
	return (0);
}

void	is_player(t_game *game)
{
	int		i;
	int		j;
	char	**tab3;

	j = -1;
	tab3 = game->tab3;
	while (tab3[++j])
	{
		i = 0;
		while (tab3[j][i])
		{
			if (tab3[j][i] == 'N' || tab3[j][i] == 'S'
				|| tab3[j][i] == 'E' || tab3[j][i] == 'W')
			{
				if (game->is_player != 'H')
					throw_error66(game);
				if (!check_zero(game, i, j))
					throw_error4(game);
				game->is_player = tab3[j][i];
			}
			else if (tab3[j][i] != ' ' && !ft_isbinary(tab3[j][i]))
				throw_error4(game);
			i++;
		}
	}
}

int	find_longer_line(char **map)
{
	int	i;
	int	j;
	int	size;

	size = 0;
	i = 0;
	j = 0;
	while (map[i])
	{
		j = ft_strlen(map[i]);
		if (j > size)
			size = j;
		i++;
	}
	return (size);
}
