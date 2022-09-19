/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printtiles.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hspriet <hspriet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 17:27:11 by hspriet           #+#    #+#             */
/*   Updated: 2022/04/26 17:10:56 by hspriet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_img(t_root *root, char **tab)
{
	int		height;
	int		width;
	t_img	size;

	height = ft_strlen(tab[0]) * 128;
	width = root->size * 128;
	root->mlx = mlx_init();
	root->win = mlx_new_window(root->mlx, height, width, "so_long");
	root->txtr[PLAYER].img = mlx_xpm_file_to_image(root->mlx,
			"./images/player.xpm", &size.img_width, &size.img_height);
	root->txtr[COLLEC].img = mlx_xpm_file_to_image(root->mlx,
			"./images/collec.xpm", &size.img_width, &size.img_height);
	root->txtr[EXIT].img = mlx_xpm_file_to_image(root->mlx,
			"./images/porte.xpm", &size.img_width, &size.img_height);
	root->txtr[GRASS].img = mlx_xpm_file_to_image(root->mlx,
			"./images/tiles.xpm", &size.img_width, &size.img_height);
	root->txtr[WALL].img = mlx_xpm_file_to_image(root->mlx,
			"./images/mur.xpm", &size.img_width, &size.img_height);
	root->txtr[WALL2].img = mlx_xpm_file_to_image(root->mlx,
			"./images/mur2.xpm", &size.img_width, &size.img_height);
	root->txtr[WALL3].img = mlx_xpm_file_to_image(root->mlx,
			"./images/mur3.xpm", &size.img_width, &size.img_height);
	root->txtr[WALL4].img = mlx_xpm_file_to_image(root->mlx,
			"./images/mur4.xpm", &size.img_width, &size.img_height);
	check_img(root);
}

int	is_finish(t_root *root)
{
	if (root->is_collect == 0)
		return (1);
	return (0);
}

void	finish(t_root *root, char **tab)
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
		mlx_destroy_image(root->mlx, root->txtr[i].img);
		i++;
	}
	mlx_destroy_window(root->mlx, root->win);
	mlx_destroy_display(root->mlx);
	free(root->mlx);
	free(root);
	exit(EXIT_SUCCESS);
}

void	print_txtr(t_root *root, int x, int y, int type)
{
	mlx_put_image_to_window(root->mlx, root->win, root->txtr[type].img, x, y);
}

void	print_tiles(t_root *a, char **tab)
{
	a->y = -1;
	while (tab[++a->y])
	{
		a->x = -1;
		while (tab[a->y][++a->x])
		{
			if (tab[a->y][a->x] == '1')
				print_txtr(a, a->x * 128, a->y * 128, WALL + (a->step % 4));
			if (tab[a->y][a->x] == '0')
				print_txtr(a, a->x * 128,
					a->y * 128, WALL + ((a->step + 1) % 4));
			if (tab[a->y][a->x] == 'P')
			{
				print_txtr(a, a->x * 128, a->y * 128, PLAYER);
				a->yy = a->y;
				a->xx = a->x;
			}
			if (tab[a->y][a->x] == 'C')
				print_txtr(a, a->x * 128, a->y * 128, COLLEC);
			if (tab[a->y][a->x] == 'E')
				print_txtr(a, a->x * 128, a->y * 128, EXIT);
		}
	}
	a->x = a->xx;
	a->y = a->yy;
}
