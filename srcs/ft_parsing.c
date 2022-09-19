/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpol <rpol@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 10:18:27 by rpol              #+#    #+#             */
/*   Updated: 2022/02/26 06:31:14 by rpol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_init_bsh(t_vars *v, t_map *m0, t_map *m1)
{
	v->dx = abs(m1->rx - m0->rx);
	if (m0->rx < m1->rx)
		v->sx = 1;
	else
		v->sx = -1;
	v->dy = abs(m1->ry - m0->ry);
	if (m0->ry < m1->ry)
		v->sy = 1;
	else
		v->sy = -1;
	if (v->dx > v->dy)
		v->er = v->dx / 2;
	else
		v->er = -v->dy / 2;
}

int	ft_atoip(t_vars *vars, int sign, int nb)
{
	char	*str;

	str = vars->s;
	while (*str == ' ')
		str++;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		nb = (nb * 10) + (*str - '0');
		str++;
	}
	if (*str == ',')
	{
		str++;
		while (ft_isalnum(*str))
			str++;
	}
	vars->s = str;
	return (nb * sign);
}

int	ft_parsing(int ac, char **av, t_vars *vars)
{
	vars->err = 0;
	vars->winx = 0;
	vars->winy = 0;
	vars->size = 1000;
	if (ac != 2)
		return (fput("ERROR WRONG ARGUMENTS\n"));
	if (ft_strlen(av[1]) == 0)
		return (fput("ERROR EMPTY NAME\n"));
	vars->fd = open(av[1], O_RDONLY);
	if (vars->fd < 1)
		return (fput("ERROR CANT OPEN FILE\n"));
	gnl(vars);
	if (vars->err == 1)
		return (ft_freelka(vars), fput("ERROR MAP\n"));
	if (vars->err == 2)
		return (ft_freelka(vars), fput("ERROR GNL/MALLOC\n"));
	if (!ft_linkinit(vars))
		return (ft_freelka(vars), 0);
	vars->name = ft_strjoinc("fdf ", av[1]);
	return (1);
}
