/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_linkinit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpol <rpol@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 12:52:51 by rpol              #+#    #+#             */
/*   Updated: 2022/02/21 12:26:52 by rpol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_freelk(t_vars *vars)
{
	t_map	*m;

	while (vars->m3->next != NULL)
	{
		m = vars->m3;
		vars->m3 = vars->m3->next;
		free(m);
	}
	free(vars->m3);
}

void	ft_freelka(t_vars *v)
{
	t_tab	*t;

	while (v->tab->next != NULL)
	{
		t = v->tab;
		v->tab = v->tab->next;
		free(t->s);
		free(t);
	}
	free(v->tab->s);
	free(v->tab);
}

static void	ft_getrel(t_vars *vars, t_map *map, int px, int py)
{
	map->x = px;
	map->y = py;
	map->z = ft_atoip(vars, 1, 0);
	if (vars->posx == vars->winx - 1)
	{
		vars->posx = 0;
		vars->posy++;
		vars->l = vars->l->next;
		vars->s = vars->l->s;
	}
	else
		vars->posx++;
}

static int	ft_initstk(t_vars *vars)
{
	t_map	*m;

	vars->err = 0;
	vars->stdc = 0x00FFFF;
	vars->posx = 0;
	vars->posy = 0;
	vars->zoom = 0.5 * (vars->size / vars->winx);
	vars->alt = 0.5;
	vars->a = -30;
	vars->movex = vars->size / 4;
	vars->movey = vars->size / 5;
	vars->l = vars->tab;
	vars->s = vars->l->s;
	m = malloc(sizeof(t_map));
	if (!m)
		return (vars->err = 1, 0);
	ft_getrel(vars, m, vars->posx, vars->posy);
	m->c = vars->stdc;
	m->next = NULL;
	vars->m3 = m;
	return (1);
}

int	ft_linkinit(t_vars *vars)
{
	t_map	*map;

	if (!ft_initstk(vars))
		return (0);
	map = vars->m3;
	while (vars->err == 0 && vars->posy < vars->winy)
	{
		map->next = malloc(sizeof(t_map));
		if (!map->next)
			return (ft_freelk(vars), 0);
		map = map->next;
		ft_getrel(vars, map, vars->posx, vars->posy);
		map->c = vars->stdc;
	}
	map->next = NULL;
	return (1);
}
