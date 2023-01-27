/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_like_to_move_it.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpol <rpol@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 17:31:45 by hspriet           #+#    #+#             */
/*   Updated: 2023/01/27 13:59:56 by rpol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

int	is_new_pos_lava_move(t_game *g, float x, float y)
{
	int	tab_x;
	int	tab_y;

	if (x < 0 || y < 0)
		return (1);
	tab_x = floor(x / g->ts);
	tab_y = floor(y / g->ts);
	if (tab_x > ft_strlen(g->map[0]))
		return (1);
	if (tab_y >= (ft_tablen(g->map)))
		return (1);
	if (g->map[tab_y][tab_x] == '1' || g->map[tab_y][tab_x] == '0')
		return (0);
	return (1);
}

float	normalise_rad(float rad)
{
	rad = remainder(rad, 2 * PI);
	if (rad < 0)
		rad = (2 * PI) + rad;
	return (rad);
}

void	update_player(t_game *g)
{
	float		new_x;
	float		new_y;

	g->rad = normalise_rad(g->rad);
	g->rad += (float)g->turn * g->rotation_speed;
	new_x = g->p->x - (sin(g->rad) * g->side * g->side_speed);
	new_y = g->p->y + (cos(g->rad) * g->side * g->side_speed);
	if (g->side == 0)
	{
		new_x = (double)g->p->x + (cos(g->rad) * g->step * g->step_speed);
		new_y = (double)g->p->y + (sin(g->rad) * g->step * g->step_speed);
	}
	if (!is_new_pos_lava_move(g, new_x, new_y))
	{
		g->p->x = new_x;
		g->p->y = new_y;
	}
}
