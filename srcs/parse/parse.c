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
	if (ret == NULL)
		throw_error2(game, tab);
	while (ret != NULL)
	{
		tab = ft_strjoin(tab, ret);
		tab = ft_strjoin(tab, " ");
		tmp = ret;
		i++;
		ret = get_next_line(game->fd);
		if (ret != NULL)
			free(tmp);
	}
	return (free(tmp), tab);
}




void parse_settings(t_game *game)
{
	char 	**tab;
	char 	*str;
	char	*compas;
	char	*compas2;
	int		i = 0;

	tab = game->tab2;
	while (tab[i])
	{
		str = ft_strtrim(tab[i], " ");
		if (!str)
			throw_error3(game, *tab);
		else
		{
			compas2 = ft_strldup(str, 1);
			compas = ft_strldup(str, 2);
		}
		if (!compas)
			throw_error3(game, *tab);
		if (!ft_strcmp(compas, "NO"))
		{
			str = ft_substr(str, 2, ft_strlen(str) - 2);
			if (game->no_texture)
				throw_error3(game, *tab);
			game->no_texture = ft_strtrim(str, " ");
			game->truc_parse++;
		}
		else if (!ft_strcmp(compas, "SO"))
		{
			str = ft_substr(str, 2, ft_strlen(str) - 2);
			if (game->so_texture)
				throw_error3(game, *tab);
			game->so_texture = ft_strtrim(str, " ");
			game->truc_parse++;
		}
		else if (!ft_strcmp(compas, "WE"))
		{
			str = ft_substr(str, 2, ft_strlen(str) - 2);
			if (game->we_texture)
				throw_error3(game, *tab);
			game->we_texture = ft_strtrim(str, " ");
			game->truc_parse++;
		}
		else if (!ft_strcmp(compas, "EA"))
		{
			str = ft_substr(str, 2, ft_strlen(str) - 2);
			if (game->ea_texture)
				throw_error3(game, *tab);
			game->ea_texture = ft_strtrim(str, " ");
			game->truc_parse++;
		}
		else if (!ft_strcmp(compas2, "F"))
		{
			str = ft_substr(str, 1, ft_strlen(str) - 1);
			if (game->floor_rgb)
				throw_error3(game, *tab);
			game->floor_rgb = ft_strtrim(str, " ");
			game->truc_parse++;
		}
		else if (!ft_strcmp(compas2, "C"))
		{
			str = ft_substr(str, 1, ft_strlen(str) - 1);
			if (game->ceiling_rgb)
				throw_error3(game, *tab);
			game->ceiling_rgb = ft_strtrim(str, " ");
			game->truc_parse++;
		}
		else if (game->truc_parse != 6)
			throw_error3(game, *tab);
		else
			break ;
		i++;
		free(compas2);
		free(compas);
		free(str);
	}
	free(str);
	free(compas2);
	free(compas);
}

void	final_map(t_game *game)
{
	int		k;
	int		j;
	char	*str;
	char	*str2;

	j = 6;
	game->tab3 = malloc(sizeof(char **) * (find_longer_collum(game->tab) - 5));
	if (!game->tab3)
		return ;
	while (j < find_longer_collum(game->tab2))
	{
		k = 0;
		str = ft_strdup(game->tab2[j]);
		game->tab3[j - 6] = ft_strdup(str);
		k = ft_strlen(str);
		free(str);
		while (k < find_longer_line(game->tab2))
		{
			str2 = game->tab3[j];
			str = ft_strjoin4(str2, " ");
			game->tab3[j] = str;
			free(str2);
			k++;
		}
		j++;
	}
	game->tab3[j - 6] = NULL;
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
	if_zero(game, game->tab3);
	is_line_left(game);
	is_line_right(game);
	is_player(game);
	is_collunm_bot(game);
	game->sky_color = parse_rgb_color(game, game->ceiling_rgb);
	game->ground_color = parse_rgb_color(game, game->floor_rgb);
}
