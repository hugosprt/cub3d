/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hspriet <hspriet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 19:59:59 by hspriet           #+#    #+#             */
/*   Updated: 2023/02/01 20:00:00 by hspriet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

void	parse_help6(t_game *game, char *str)
{
	str = ft_substr(str, 1, ft_strlen(str) - 1);
	game->ceiling_rgb = ft_strtrim(str, " ");
	game->truc_parse++;
	free(str);
}

char	*make_str(t_game *game, int i)
{
	char	*str;

	str = ft_strtrim(game->tab2[i], " ");
	if (!str)
		throw_error3(game, *game->tab2);
	return (str);
}
