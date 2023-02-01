/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hspriet <hspriet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 19:59:56 by hspriet           #+#    #+#             */
/*   Updated: 2023/02/01 19:59:57 by hspriet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

void	parse_help(t_game *game, char *str)
{
	str = ft_substr(str, 2, ft_strlen(str) - 2);
	game->no_texture = ft_strtrim(str, " ");
	game->truc_parse++;
	free(str);
}

void	parse_help2(t_game *game, char *str)
{
	str = ft_substr(str, 2, ft_strlen(str) - 2);
	game->so_texture = ft_strtrim(str, " ");
	game->truc_parse++;
	free(str);
}

void	parse_help3(t_game *game, char *str)
{
	str = ft_substr(str, 2, ft_strlen(str) - 2);
	game->ea_texture = ft_strtrim(str, " ");
	game->truc_parse++;
	free(str);
}

void	parse_help4(t_game *game, char *str)
{
	str = ft_substr(str, 2, ft_strlen(str) - 2);
	game->we_texture = ft_strtrim(str, " ");
	game->truc_parse++;
	free(str);
}

void	parse_help5(t_game *game, char *str)
{
	str = ft_substr(str, 1, ft_strlen(str) - 1);
	game->floor_rgb = ft_strtrim(str, " ");
	game->truc_parse++;
	free(str);
}
