/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpol <rpol@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 22:25:42 by rpol              #+#    #+#             */
/*   Updated: 2023/01/30 00:24:24 by rpol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

void	ft_bsh_print(t_game *g, int fx, int fy)
{
	int	x;
	int	y;

	ft_init_bsh(g, fx, fy);
	x = ((int)g->p->x % g->wwidth);
	y = ((int)g->p->y % g->wheight);
	while (1)
	{
		img_put_pixel(x, y, g, 0x00FF0000);
		if ((x == fx && y == fy))
			break ;
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

void	player_render(t_game *g, unsigned int color)
{
	int	x;
	int	y;
	int	x_finish;
	int	y_finish;

	x_finish = (((int)g->p->x) % g->wwidth) + 3;
	y_finish = (((int)g->p->y) % g->wheight) + 3;
	x = (((int)g->p->x) % g->wwidth) - 2;
	while (x <= x_finish)
	{
		y = (((int)g->p->y) % g->wheight) - 2;
		while (y < y_finish)
		{
			img_put_pixel(x, y, g, color);
			y++;
		}
		x++;
	}
	x = (((int)g->p->x % g->wwidth) - (cos(g->rad) * 7));
	y = ((int)g->p->y % g->wheight) - (sin(g->rad) * 7);
	ft_bsh_print(g, x, y);
}

int	minimap_move(t_game *g, int x, int y, int i)
{
	y = g->p->y;
	if (i == 0)
	{
		if (y >= g->wheight)
		{
			while (y >= g->wheight)
			{
				y -= g->wheight;
				i++;
			}
		}
		return (i);
	}
	i = 0;
	if (x >= g->wwidth)
	{
		while (x >= g->wwidth)
		{
			x -= g->wwidth;
			i++;
		}
	}
	return (i);
}

void	rectangle_tilesize(t_game *g, int x_s, int y_s, unsigned int color)
{
	int	x;
	int	y;
	int	x_finish;
	int	y_finish;

	y = (y_s * g->ts) - (30 * minimap_move(g, g->p->x, 0, 0));
	x = x_s * g->ts - (45 * minimap_move(g, g->p->x, 0, 1));
	x_finish = x + g->ts;
	y_finish = y + g->ts;
	while (x <= x_finish)
	{
		y = (y_s * g->ts) - (30 * minimap_move(g, g->p->x, 0, 0));
		while (y < y_finish)
		{
			img_put_pixel(x, y, g, color);
			y++;
		}
		x++;
	}
}

void	print_map(t_game *g, char **tab)
{
	int	off_y;
	int	off_x;

	off_y = minimap_move(g, g->p->x, 0, 0) * floor((g->wheight / g->ts));
	off_x = minimap_move(g, g->p->x, 0, 1) * floor((g->wwidth / g->ts));
	g->p->i = 1;
	g->y = -1 + off_y;
	while (tab[++g->y] && g->y <= off_y + floor((g->wheight / g->ts)))
	{
		g->x = -1 + off_x;
		while (tab[g->y][++g->x] && g->x <= off_x + floor((g->wwidth / g->ts)))
		{
			if (tab[g->y][g->x] == '1')
				rectangle_tilesize(g, g->x - off_x, g->y - off_y, g->sky_color);
			if (tab[g->y][g->x] == '0')
				rectangle_tilesize(g, g->x - off_x, g->y - off_y,
					g->ground_color);
		}
	}
	player_render(g, 0x00FF0000);
}
