/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpol <rpol@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 22:28:05 by rpol              #+#    #+#             */
/*   Updated: 2023/01/29 22:36:15 by rpol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

void	calculate_offset(t_game *g, int y, int wallheight)
{
	int	distance;

	if (g->texture == 'n' || g->texture == 's')
		g->off_x = (g->x_intercept % g->ts);
	else if (g->texture == 'e' || g->texture == 'w')
		g->off_x = (g->y_intercept % g->ts);
	distance = y + (wallheight / 2) - (g->wheight / 2);
	g->off_y = distance * ((float)g->ts / wallheight);
}

int	is_new_pos_lavab(t_game *g, float x, float y)
{
	int	tab_x;
	int	tab_y;

	if (x < 0 || x >= g->x_max || y < 0 || y >= g->y_max)
		return (1);
	tab_x = floor(x / g->ts);
	tab_y = floor(y / g->ts);
	if (tab_x < 0 || tab_y < 0 || tab_x > g->x_mmax || tab_y > g->y_mmax)
		return (1);
	if (g->tab3[tab_y][tab_x] == '0')
		return (0);
	return (1);
}

int	is_new_pos_lava(t_game *g, int x, int y)
{
	int	tab_x;
	int	tab_y;

	tab_x = (int)floor(x / g->ts);
	tab_y = (int)floor(y / g->ts);
	if (tab_x < 0 || tab_y < 0 || tab_x > g->x_mmax || tab_y > g->y_mmax)
		return (1);
	if (g->tab3[tab_y][tab_x] == '0')
		return (0);
	return (1);
}

void	ft_find_distance(t_game *g, float rad)
{
	int	x;
	int	y;

	g->radr = rad;
	x = g->p->x - (cos(rad) * 10000);
	y = g->p->y - (sin(rad) * 10000);
	ft_bsh_distance(g, x, y);
	calculate_texture(g);
}

void	ray_cast(t_game *g)
{
	int		id;
	float	firstrad;
	float	step;

	g->p->i = 1;
	if (is_new_pos_lava(g, g->p->x, g->p->y))
		return (rectangle_window_size(g, 255));
	step = (60 * (PI / 180)) / g->wwidth;
	firstrad = g->rad - (step * (g->wwidth / 2));
	id = 0;
	while (id < 1200)
	{
		ft_find_distance(g, firstrad);
		draw_ray(g, id);
		firstrad += step;
		id++;
	}
}
