/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hspriet <hspriet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 18:50:35 by hspriet           #+#    #+#             */
/*   Updated: 2022/04/26 17:20:20 by hspriet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_truc(int keycode, t_root *root)
{
	if (keycode == 115)
		move_down(root, root->tab);
	if (keycode == 119)
		move_up(root, root->tab);
	if (keycode == 100)
		move_right(root, root->tab);
	if (keycode == 97)
		move_left(root, root->tab);
	if (keycode == 65307)
		finish(root, root->tab);
	return (0);
}

int	ft_truc2(t_root *root)
{
	ft_truc(65307, root);
	return (0);
}

void	throw_error(t_root *root, char *tab)
{
	ft_printf("error\n");
	free(tab);
	free(root);
	exit(EXIT_FAILURE);
}

void	crash(t_root *root, char **tab)
{
	int	i;

	(void) tab;
	i = 0;
	while (root->tab[i] != NULL)
	{
		free(root->tab[i]);
		i++;
	}
	free(root->tab);
	i = 0;
	while (i < 8)
	{
		if (root->txtr[i].img != NULL)
			mlx_destroy_image(root->mlx, root->txtr[i].img);
		i++;
	}
	mlx_destroy_window(root->mlx, root->win);
	mlx_destroy_display(root->mlx);
	free(root->mlx);
	free(root);
	ft_printf("error\n");
	exit(EXIT_FAILURE);
}

int	main(int ac, char **av)
{
	t_root	*root;
	char	*str;

	if (ac != 2)
	{
		write(2, "Error\n", 6);
		return (0);
	}
	root = malloc(sizeof(t_root));
	struct_init(root, av[1]);
	str = parse(root);
	root->tab = ft_split(str, '\n');
	free(str);
	init_img(root, root->tab);
	mlx_hook(root->win, 02, 1l << 0, ft_truc, root);
	mlx_hook(root->win, 17, 1L << 5, ft_truc2, root);
	print_tiles(root, root->tab);
	mlx_loop(root->mlx);
	free(root);
	return (0);
}
