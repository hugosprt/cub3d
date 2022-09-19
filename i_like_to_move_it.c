/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_like_to_move_it.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hspriet <hspriet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 17:31:45 by hspriet           #+#    #+#             */
/*   Updated: 2022/04/12 18:52:26 by hspriet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	move_up(t_root *root, char **tab)
{
	if (tab[root->y -1][root->x] == '1' ||
		(!is_finish(root) && tab[root->y - 1][root->x] == 'E'))
		print_tiles(root, tab);
	else
	{
		if (tab[root->y -1][root->x] == 'E' && is_finish(root))
			finish(root, tab);
		if (tab[root->y -1][root->x] == 'C')
			root->is_collect = root->is_collect - 1;
		tab[root->y][root->x] = '0';
		root->y = root->y - 1;
		tab[root->y][root->x] = 'P';
		root->step = root->step + 1;
		ft_printf("hop la un pas de plus:%d\n", root->step);
		print_tiles(root, tab);
	}
}

void	move_down(t_root *root, char **tab)
{
	if (tab[root->y + 1][root->x] == '1' ||
		(!is_finish(root) && tab[root->y + 1][root->x] == 'E'))
		print_tiles(root, tab);
	else
	{
		if (tab[root->y + 1][root->x] == 'E' && is_finish(root))
			finish(root, tab);
		if (tab[root->y + 1][root->x] == 'C')
			root->is_collect = root->is_collect - 1;
		tab[root->y][root->x] = '0';
		root->y = root->y + 1;
		tab[root->y][root->x] = 'P';
		root->step = root->step + 1;
		ft_printf("hop la un pas de plus:%d\n", root->step);
		print_tiles(root, tab);
	}
}

void	move_right(t_root *root, char **tab)
{
	if (tab[root->y][root->x + 1] == '1' ||
		(!is_finish(root) && tab[root->y][root->x + 1] == 'E'))
		print_tiles(root, tab);
	else
	{
		if (tab[root->y][root->x + 1] == 'E' && is_finish(root))
			finish(root, tab);
		if (tab[root->y][root->x + 1] == 'C')
			root->is_collect = root->is_collect - 1;
		tab[root->y][root->x] = '0';
		root->x = root->x + 1;
		tab[root->y][root->x] = 'P';
		root->step = root->step + 1;
		ft_printf("hop la un pas de plus:%d\n", root->step);
		print_tiles(root, tab);
	}
}

void	move_left(t_root *root, char **tab)
{
	if (tab[root->y][root->x - 1] == '1' ||
		(!is_finish(root) && tab[root->y][root->x - 1] == 'E'))
		print_tiles(root, tab);
	else
	{
		if (tab[root->y][root->x - 1] == 'E' && is_finish(root))
			finish(root, tab);
		if (tab[root->y][root->x - 1] == 'C')
			root->is_collect = root->is_collect - 1;
		tab[root->y][root->x] = '0';
		root->x = root->x - 1;
		tab[root->y][root->x] = 'P';
		root->step = root->step + 1;
		ft_printf("hop la un pas de plus:%d\n", root->step);
		print_tiles(root, tab);
	}
}
