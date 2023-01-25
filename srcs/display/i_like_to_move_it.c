/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_like_to_move_it.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpol <rpol@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 17:31:45 by hspriet           #+#    #+#             */
/*   Updated: 2023/01/25 01:33:55 by rpol             ###   ########.fr       */
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

// void	move_right(t_game *g, double n)
// {
// 	int	new_x;
// 	int	new_y;

// 	new_x = g->p->x - (int)(n * (sin(g->rad) * g->step_speed));
// 	new_y = g->p->y + (int)(n * (cos(g->rad) * g->step_speed));
// 	if (!is_new_pos_lava(g, new_x, new_y))
// 	{
// 		g->p->x = new_x;
// 		g->p->y = new_y;
// 	}
// }

// void	move_up(t_game *g, double n)
// {
// 	int	new_x;
// 	int	new_y;

// 	new_x = g->p->x + (int)(n * (cos(g->rad) * g->step_speed));
// 	new_y = g->p->y + (int)(n * (sin(g->rad) * g->step_speed));
// 	if (!is_new_pos_lava(g, new_x, new_y))
// 	{
// 		g->p->x = new_x;
// 		g->p->y = new_y;
// 	}
// }

void	rad2angle(t_game *g)
{
	if (g->p->a < 0)
	{
		g->p->a += 360;
		rad2angle(g);
	}
	if (g->p->a > 360)
	{
		g->p->a -= 360;
		rad2angle(g);
	}
	g->rad = (g->p->a * (PI / 180));
}

void	update_player(t_game *g)
{
	float		new_x;
	float		new_y;

	g->p->a += g->turn * g->rotation_speed;
	rad2angle(g);
	new_x = g->p->x - (sin(g->rad) * g->side * g->step_speed);
	new_y = g->p->y + (cos(g->rad) * g->side * g->step_speed);
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
