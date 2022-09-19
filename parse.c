/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hspriet <hspriet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 15:40:05 by hspriet           #+#    #+#             */
/*   Updated: 2022/04/13 19:13:25 by hspriet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "get_next_line.h"

void	check_error(t_root *root, char *tab)
{
	if (root->is_player != 1 || root->is_exit != 1
		|| root->is_valid != 1 || root->is_collect < 1)
		throw_error(root, tab);
}

char	*parse(t_root *root)
{
	char		*ret;
	char		*tmp;
	char		*tab;

	tab = NULL;
	if (root->fd == -1)
		throw_error(root, tab);
	ret = get_next_line(root->fd);
	if (ret == NULL)
		throw_error(root, tab);
	firstlast(root, ret);
	while (ret != NULL)
	{
		mid(root, ret);
		tab = ft_strjoin(tab, ret);
		tmp = ret;
		root->size++;
		ret = get_next_line(root->fd);
		if (ft_strlen_buff(ret) != ft_strlen_buff(tmp) && ret != NULL)
			root->is_valid = 0;
		if (ret != NULL)
			free(tmp);
	}
	firstlast(root, tmp);
	return (free(tmp), check_error(root, tab), tab);
}

void	struct_init(t_root *root, char *file)
{
	root->x = 0;
	root->y = 0;
	root->is_player = 0;
	root->is_exit = 0;
	root->is_valid = 1;
	root->size = 0;
	root->step = 0;
	root->yy = 0;
	root->xx = 0;
	root->fd = open(file, O_RDONLY);
	root->is_collect = 0;
}

void	mid(t_root *root, char *av)
{
	int	i;

	i = 0;
	while (av[i] && av[i] != '\n')
	{
		if ((av[i] != '1' && i == 0) || (av[i] != '1' && i == ft_strlen(av)))
			root->is_valid = 0;
		if (av[i] == '1')
			root->is_wall += 1;
		else if (av[i] == 'P')
			root->is_player += 1;
		else if (av[i] == 'E')
			root->is_exit += 1;
		else if (av[i] == 'C')
			root->is_collect += 1;
		else if (av[i] != '0')
			root->is_valid = 0;
		i++;
	}
}

void	firstlast(t_root *root, char *av)
{
	int	i;

	i = 0;
	while (av[i] != '\n' && av[i])
	{
		if (av[i] != '1')
			root->is_valid = 0;
		i++;
	}
}
