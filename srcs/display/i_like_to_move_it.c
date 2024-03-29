/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_like_to_move_it.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpol <rpol@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 17:31:45 by hspriet           #+#    #+#             */
/*   Updated: 2023/01/29 21:11:19 by rpol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

int	key_released(int keycode, t_game *game)
{
	if (keycode == 115)
		game->step = 0;
	if (keycode == 119)
		game->step = 0;
	if (keycode == 100)
		game->side = 0;
	if (keycode == 97)
		game->side = 0;
	if (keycode == 65361)
		game->turn = 0;
	if (keycode == 65363)
		game->turn = 0;
	if (keycode == 65307)
		mlx_loop_end(game->mlx);
	return (0);
}

int	key_pressed(int keycode, t_game *game)
{
	if (keycode == 115)
		game->step += 1;
	if (keycode == 119)
		game->step -= 1;
	if (keycode == 100)
		game->side -= 1;
	if (keycode == 97)
		game->side += 1;
	if (keycode == 65361)
		game->turn -= 1;
	if (keycode == 65363)
		game->turn += 1;
	if (keycode == 65307)
		mlx_loop_end(game->mlx);
	return (0);
}

int	is_new_pos_lava_move(t_game *g, float x, float y)
{
	int	tab_x;
	int	tab_y;

	if (x < 0 || y < 0)
		return (1);
	tab_x = floor(x / g->ts);
	tab_y = floor(y / g->ts);
	if (tab_x > ft_strlen(g->tab3[0]))
		return (1);
	if (tab_y >= (ft_tablen(g->tab3)))
		return (1);
	if (g->tab3[tab_y][tab_x] == '1' || g->tab3[tab_y][tab_x] == '0')
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
