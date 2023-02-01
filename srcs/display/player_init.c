/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpol <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 22:46:25 by rpol              #+#    #+#             */
/*   Updated: 2023/02/01 19:29:42 by rpol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

void	mlx_fail_exit(t_game *g)
{
	ft_putstr_fd("Error, MLX could not be initialised\n", 2);
	finish(g);
}

int	ft_tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

void	init_player_param(t_game *g)
{
	g->rotation_speed = PI / 90;
	g->step_speed = 4;
	g->side_speed = 2;
	g->side = 0;
	g->step = 0;
	g->turn = 0;
	g->fov = 60 * (PI / 180);
	g->p = malloc(sizeof(t_player));
	g->p->x = 0;
	g->p->y = 0;
	g->p->i = 0;
	g->t_n = NULL;
	g->t_s = NULL;
	g->t_e = NULL;
	g->t_w = NULL;
	g->win = NULL;
}

float	where_is_player_facing(char direction)
{
	if (direction == 'N')
		return (PI / 2);
	if (direction == 'S')
		return (PI);
	if (direction == 'W')
		return ((3 * PI) / 2);
	if (direction == 'E')
		return (2 * PI);
	return (PI / 2);
}

void	init_player_position(t_game *g, char **tab)
{
	g->y = -1;
	while (tab[++g->y])
	{
		g->x = -1;
		while (tab[g->y][++g->x])
		{
			if (tab[g->y][g->x] == 'N' || tab[g->y][g->x] == 'S' ||
				tab[g->y][g->x] == 'E' || tab[g->y][g->x] == 'W')
			{
				g->p->x = (g->x * g->ts) + (g->ts / 2);
				g->p->y = (g->y * g->ts) + (g->ts / 2);
				g->rad = where_is_player_facing(tab[g->y][g->x]);
				g->tab3[g->y][g->x] = '0';
			}
		}
	}
	g->x_mmax = ft_strlen(g->tab3[0]);
	g->y_mmax = ft_tablen(g->tab3) - 1;
	g->x_max = g->ts * g->x_mmax;
	g->y_max = g->ts * g->y_mmax;
}
