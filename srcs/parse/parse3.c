#include "../../includes/cub.h"

void	parse_help6(t_game *game, char *str, char *compas, char *compas2)
{
	str = ft_substr(str, 1, ft_strlen(str) - 1);
	if (game->ceiling_rgb)
		leave(game, str, compas, compas2);
	game->ceiling_rgb = ft_strtrim(str, " ");
	game->truc_parse++;
	free(str);
}

char	*make_str(t_game *game, int i)
{
	char	*str;

	str = ft_strtrim(game->tab2[i], " ");
	if (!str)
		throw_error3(game, *game->tab2);
	return (str);
}