/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hspriet <hspriet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 20:00:03 by hspriet           #+#    #+#             */
/*   Updated: 2023/02/01 20:00:04 by hspriet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

int	check_rgb_component(const char *s, int *i, int *value)
{
	int	len;

	len = 0;
	while (s[*i] != ',' && s[*i] != '\0')
	{
		if (ft_isdigit(s[*i]))
		{
			*value = (*value * 10) + (s[*i] - '0');
			len++;
		}
		else
			return (-1);
		(*i)++;
	}
	if (s[*i] == '\0' && len == 0)
	{
		return (-1);
	}
	(*i)++;
	return (0);
}

int	check_valid_input(const char *s, int *r, int *g, int *b)
{
	int	i;

	i = 0;
	if (check_rgb_component(s, &i, r) == -1)
		return (-1);
	if (check_rgb_component(s, &i, g) == -1)
		return (-1);
	if (check_rgb_component(s, &i, b) == -1)
		return (-1);
	return (0);
}

int	how_manyvirgule(char *s)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == ',')
			count++;
		i++;
	}
	if (count == 2)
		return (0);
	return (1);
}

int	parse_rgb_color(t_game *game, char *s)
{
	int	r;
	int	g;
	int	b;

	r = 0;
	g = 0;
	b = 0;
	if (how_manyvirgule(s))
		throw_error4(game);
	if (check_valid_input(s, &r, &g, &b) == -1)
	{
		throw_error4(game);
	}
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		throw_error4(game);
	}
	return ((r << 16) | (g << 8) | b);
}
