/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hspriet <hspriet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 19:59:42 by hspriet           #+#    #+#             */
/*   Updated: 2023/02/02 12:02:22 by hspriet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

void	free_texture(t_game *g)
{
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
}

void	throw_error5(t_game *g)
{
	int	i;

	i = -1;
	while (g->tab[++i] != NULL)
		free(g->tab[i]);
	free_texture(g);
	free(g->tab);
	i = -1;
	while (g->tab2[++i] != NULL)
		free(g->tab2[i]);
	free(g->tab2);
	free(g->p);
	free(g);
	ft_printf("error description\n");
	exit(EXIT_FAILURE);
}
