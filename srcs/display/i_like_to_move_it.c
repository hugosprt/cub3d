/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_like_to_move_it.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpol <rpol@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 17:31:45 by hspriet           #+#    #+#             */
/*   Updated: 2022/09/28 18:13:15 by rpol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

void	move_right(t_game *root, int n)
{
	if (n == 1)
	{
		root->p->x += 10;
		ft_printf("hop la un pas de plus:%d\n", n);
		print_tiles(root, root->tab);
	}
	else
	{
		root->p->x -= 10;
		ft_printf("hop la un pas de plus:%d\n", n);
		print_tiles(root, root->tab);
	}
}


void	move_up(t_game *root, int n)
{
	if (n == 1)
	{
		root->p->y -= 10;
		ft_printf("hop la un pas de plus:%d\n", n);
		print_tiles(root, root->tab);
	}
	else
	{
		root->p->y += 10;
		ft_printf("hop la un pas de plus:%d\n", n);
		print_tiles(root, root->tab);
	}
}

void	rotate(t_game *root, int n)
{
	if (root->tab[root->y][root->x - 1] == '1')
		print_tiles(root, root->tab);
	else
	{
		root->tab[root->y][root->x] = '0';
		root->x = root->x - 1;
		root->tab[root->y][root->x] = 'P';
		root->step = root->step + 1;
		ft_printf("hop la un pas de plus:%d\n", n);
		print_tiles(root, root->tab);
	}
}
