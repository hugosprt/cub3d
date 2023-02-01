#include "../../includes/cub.h"

char	*parse(t_game *game)
{
	char		*ret;
	char		*tmp;
	char		*tab;
	int			i;

	i = 0;
	tab = NULL;
	if (game->fd == -1)
		throw_error(game, tab);
	ret = get_next_line(game->fd);
	if (!ret)
		throw_error2(game);
	while (ret != NULL)
	{
		tab = ft_strjoin(tab, " ");
		tab = ft_strjoin(tab, ret);
		tmp = ret;
		i++;
		ret = get_next_line(game->fd);
		if (ret != NULL)
			free(tmp);
	}
	tab = ft_strjoin(tab, "1");
	return (free(tmp), tab);
}

int	parse_select(t_game *game, char *str, char *compas, char *compas2)
{	
	if (!ft_strcmp(compas, "NO") && !game->no_texture)
		parse_help(game, str);
	else if (!ft_strcmp(compas, "SO") && !game->so_texture)
		parse_help2(game, str);
	else if (!ft_strcmp(compas, "WE") && !game->we_texture)
		parse_help4(game, str);
	else if (!ft_strcmp(compas, "EA") && !game->ea_texture)
		parse_help3(game, str);
	else if (!ft_strcmp(compas2, "C") && !game->ceiling_rgb)
		parse_help6(game, str);
	else if (!ft_strcmp(compas2, "F") && !game->floor_rgb)
		parse_help5(game, str);
	else if (compas[0] == '\0')
		game->truc++;
	else if (game->truc_parse != 6)
		leave(game, str, compas, compas2);
	else
		return (0);
	return (1);
}

void	parse_settings(t_game *game)
{
	char	*str;
	char	*compas;
	char	*compas2;
	int		i;

	i = -1;
	while (game->tab2[++i])
	{
		str = make_str(game, i);
		compas2 = ft_strldup(str, 1);
		compas = ft_strldup(str, 2);
		if (parse_select(game, str, compas, compas2))
		{
			i = i - 1 + 1;
		}
		else
			break ;
		free_help(str, compas, compas2);
	}
	if (str)
		free_help(str, compas, compas2);
}

void	final_map(t_game *game)
{
	int		k;
	int		j;
	char	*str;
	char	*str2;

	j = game->truc + 6 - 1;
	game->tab3 = malloc(sizeof(char **) * (find_longer_collum(game->tab) - 5));
	if (!game->tab3)
		return ;
	while (++j < find_longer_collum(game->tab2))
	{
		k = -1;
		str = ft_strdup(game->tab2[j]);
		game->tab3[j - (game->truc + 6)] = ft_strdup(str);
		k = ft_strlen(str);
		free(str);
		while (++k < find_longer_line(game->tab2))
		{
			str2 = game->tab3[j];
			str = ft_strjoin4(str2, " ");
			game->tab3[j] = str;
			free(str2);
		}
	}
	game->tab3[j - (game->truc + 6)] = NULL;
}

void	main_parsing(t_game *game)
{
	char	*str;

	str = parse(game);
	game->tab = ft_split(str, '\n');
	free(str);
	add_border(game);
	parse_settings(game);
	final_map(game);
	is_player(game);
	if_zero(game, game->tab3);
	is_line_left(game);
	is_line_right(game);
	is_collunm_bot(game);
	if (game->is_player == 'H')
		throw_error66(game);
	game->sky_color = parse_rgb_color(game, game->ceiling_rgb);
	game->ground_color = parse_rgb_color(game, game->floor_rgb);
}
