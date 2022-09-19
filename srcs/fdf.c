/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpol <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 14:24:07 by rpol              #+#    #+#             */
/*   Updated: 2022/02/22 18:42:42 by rpol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	fput(char *s)
{
	write(1, s, ft_strlen(s));
	return (0);
}

static void	fmlx(t_vars *vars)
{
	free(vars->name);
	ft_freelk(vars);
	ft_freelka(vars);
	if (vars->mlx)
	{
		free(vars->mlx);
		fput("ERROR WIN CREATION\n");
	}
	else
		fput("ERROR MLX INIT\n");
}

void	ft_destroy(t_vars *vars)
{
	free(vars->name);
	ft_freelk(vars);
	ft_freelka(vars);
	mlx_loop_end(vars->mlx);
	mlx_destroy_window(vars->mlx, vars->win);
	fput("window destroyed\n");
	mlx_destroy_display(vars->mlx);
	fput("display destroyed\n");
	free(vars->mlx);
	fput("HASTA LA VISTA \n");
	exit (0);
}

static int	keypress(int keycode, t_vars *vars)
{
	if (keycode == 0x0071)
		return (vars->a -= 30, ft_draw(vars));
	if (keycode == 0x0065)
		return (vars->a += 30, ft_draw(vars));
	if (keycode == 0x0073)
		return (vars->movey += 20, ft_draw(vars));
	if (keycode == 0x0077)
		return (vars->movey -= 20, ft_draw(vars));
	if (keycode == 0x0061)
		return (vars->movex -= 20, ft_draw(vars));
	if (keycode == 0x0064)
		return (vars->movex += 20, ft_draw(vars));
	if (keycode == 0x0072)
		return (vars->alt += 0.1, ft_draw(vars));
	if (keycode == 0x0066)
		return (vars->alt -= 0.1, ft_draw(vars));
	if (keycode == 0x007a)
		return (vars->zoom += 1, ft_draw(vars));
	if (keycode == 0x0078)
		return (vars->zoom -= 1, ft_draw(vars));
	if (keycode == 0x0063)
		return (vars->stdc += 420, ft_draw(vars));
	if (keycode == 0xff1b)
		return (ft_destroy(vars), 0);
	return (0);
}

int	main(int ac, char **av)
{
	t_vars	vars;

	if (!ft_parsing(ac, av, &vars))
		return (0);
	vars.mlx = mlx_init();
	if (!(vars.mlx))
		return (fmlx(&vars), 0);
	vars.win = mlx_new_window(vars.mlx, vars.size, vars.size, vars.name);
	if (!vars.win)
		return (fmlx(&vars), 0);
	ft_draw(&vars);
	mlx_hook(vars.win, 2, 1L << 0, keypress, &vars);
	mlx_loop(vars.mlx);
}
