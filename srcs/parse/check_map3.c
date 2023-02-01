/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hspriet <hspriet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 19:59:29 by hspriet           #+#    #+#             */
/*   Updated: 2023/02/01 19:59:30 by hspriet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

void	add_border(t_game	*game)
{
	int		k;
	int		j;
	char	*str;
	char	*str2;

	j = 0;
	game->tab2 = malloc(sizeof(char **) * (find_longer_collum(game->tab) + 1));
	while (j < find_longer_collum(game->tab))
	{
		k = 0;
		str = ft_strdup(game->tab[j]);
		game->tab2[j] = ft_strdup(str);
		k = ft_strlen(str);
		free(str);
		while (k < find_longer_line(game->tab))
		{
			str2 = game->tab2[j];
			str = ft_strjoin4(str2, " ");
			game->tab2[j] = str;
			free(str2);
			k++;
		}
		j++;
	}
	game->tab2[j] = NULL;
}
