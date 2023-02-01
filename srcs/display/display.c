/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpol <rpol@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 22:55:57 by rpol              #+#    #+#             */
/*   Updated: 2023/01/29 22:55:59 by rpol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

void	ft_init_bsh(t_game *g, int fx, int fy)
{
	int	x;
	int	y;

	x = ((int)g->p->x % g->wwidth);
	y = ((int)g->p->y % g->wheight);
	g->dx = abs(fx - x);
	if (x < fx)
		g->sx = 1;
	else
		g->sx = -1;
	g->dy = abs(fy - y);
	if (y < fy)
		g->sy = 1;
	else
		g->sy = -1;
	if (g->dx > g->dy)
		g->er = g->dx / 2;
	else
		g->er = -g->dy / 2;
}

void	old_pos(t_game *g, int x, int y)
{
	g->old_x = floor(x / g->ts);
	g->old_y = floor(y / g->ts);
}

void	hit_pos(t_game *g, int x, int y)
{
	g->x_intercept = x;
	g->y_intercept = y;
	g->x_wall_pos = floor(x / g->ts);
	g->y_wall_pos = floor(y / g->ts);
	g->distance = sqrt(((x - g->p->x) * (x - g->p->x))
			+ ((y - g->p->y) * (y - g->p->y)));
}

void	ft_bsh_distance(t_game *g, int fx, int fy)
{
	int	x;
	int	y;

	ft_init_bsh(g, fx, fy);
	x = g->p->x;
	y = g->p->y;
	old_pos(g, x, y);
	while (1)
	{
		if ((x == fx && y == fy) || is_new_pos_lavab(g, x, y))
			return (hit_pos(g, x, y));
		old_pos(g, x, y);
		g->e2 = g->er;
		if (g->e2 > -g->dx)
		{
			g->er -= g->dy;
			x += g->sx;
		}
		if (g->e2 < g->dy)
		{
			g->er += g->dx;
			y += g->sy;
		}
	}
}

int	render(t_game *g)
{
	if (g->step == 0 && g->side == 0 && g->turn == 0 && g->p->i > 0)
		return (0);
	else if (g->p->i > 0)
		update_player(g);
	g->img = mlx_new_image(g->mlx, g->wwidth, g->wheight);
	if (!g->img)
		return (ft_putstr_fd("Error new image\n", 2), 1);
	g->adr = mlx_get_data_addr(g->img, &g->bitsz, &g->lsz, &g->endi);
	if (is_new_pos_lava(g, g->p->x, g->p->y))
		print_map(g, g->tab3);
	else
		ray_cast(g);
	mlx_put_image_to_window(g->mlx, g->win, g->img, 0, 0);
	mlx_destroy_image(g->mlx, g->img);
	return (0);
}
