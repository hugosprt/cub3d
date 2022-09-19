/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpol <rpol@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 19:31:39 by rpol              #+#    #+#             */
/*   Updated: 2022/02/26 06:33:08 by rpol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	ft_2d(t_vars *v, double x, double y, double a)
{
	t_map	*map;
	double	px;
	double	py;
	double	z;

	map = v->m3;
	a = (((double)v->a * 3.1415926535) / 180);
	while (map != NULL)
	{
		px = map->x;
		py = map->y;
		z = (double)map->z * v->alt;
		x = (px * cos(a)) - (py * sin(a));
		y = (py * cos(a)) + (px * sin(a));
		map->rx = ((x - y) * v->zoom) + v->movex;
		map->ry = ((-z + x + y) * v->zoom) + v->movey;
		map = map->next;
	}
	return (0);
}

static int	img_put_pixel(int x, int y, t_vars *v)
{
	char	*adrtmp;
	int		lsz;
	int		bitsz;

	adrtmp = v->adr;
	lsz = v->lsz;
	bitsz = v->bitsz;
	if (x > 0 && y > 0 && x < v->size && y < v->size)
	{
		adrtmp += (y * lsz + (x * ((bitsz) / 8)));
		*(unsigned int *)adrtmp = (unsigned int)v->cc;
	}
	return (0);
}

static void	ft_bsh(t_vars *v, t_map *m0, t_map *m1)
{
	int	x;
	int	y;

	ft_init_bsh(v, m0, m1);
	x = m0->rx;
	y = m0->ry;
	v->cc = v->stdc + (m1->z * 100);
	while (1)
	{
		img_put_pixel(x, y, v);
		if ((x == m1->rx && y == m1->ry)
			|| (m1->x == 0 && m0->x == v->winx - 1))
			break ;
		v->e2 = v->er;
		if (v->e2 > -v->dx)
		{
			v->er -= v->dy;
			x += v->sx;
		}
		if (v->e2 < v->dy)
		{
			v->er += v->dx;
			y += v->sy;
		}
	}
}

static int	ft_draw2d(t_vars *v)
{
	t_map	*m;

	m = v->m3;
	v->topl = v->m3;
	while (m->next != NULL)
	{
		while (m->y < 1 && m->x < (v->winx - 1))
		{
			ft_bsh(v, m, m->next);
			m = m->next;
		}
		if (m->x < v->winx - 1)
		{
			ft_bsh(v, m, m->next);
		}
		ft_bsh(v, m, v->topl);
		if (m->y > 0)
			v->topl = v->topl->next;
		m = m->next;
	}
	ft_bsh(v, m, v->topl);
	return (1);
}

int	ft_draw(t_vars *v)
{
	ft_2d(v, 0, 0, 0);
	v->img = mlx_new_image(v->mlx, 1000, 1000);
	if (!v->img)
		return (fput("ERR IMG\n"), ft_destroy(v), 0);
	v->adr = mlx_get_data_addr(v->img, &v->bitsz, &v->lsz, &v->endi);
	ft_draw2d(v);
	mlx_put_image_to_window(v->mlx, v->win, v->img, 0, 0);
	mlx_destroy_image(v->mlx, v->img);
	return (1);
}
