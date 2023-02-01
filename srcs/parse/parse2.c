#include "../../includes/cub.h"


void	parse_help(t_game *game, char *str, char *compas, char *compas2)
{
	str = ft_substr(str, 2, ft_strlen(str) - 2);
	if (game->no_texture)
	{
		leave(game, str, compas, compas2);
	}
	game->no_texture = ft_strtrim(str, " ");
	game->truc_parse++;
	free(str);
}

void	parse_help2(t_game *game, char *str, char *compas, char *compas2)
{
	str = ft_substr(str, 2, ft_strlen(str) - 2);
	if (game->so_texture)
		leave(game, str, compas, compas2);
	game->so_texture = ft_strtrim(str, " ");
	game->truc_parse++;
	free(str);
}

void	parse_help3(t_game *game, char *str, char *compas, char *compas2)
{
	str = ft_substr(str, 2, ft_strlen(str) - 2);
	if (game->ea_texture)
		leave(game, str, compas, compas2);
	game->ea_texture = ft_strtrim(str, " ");
	game->truc_parse++;
	free(str);
}

void	parse_help4(t_game *game, char *str, char *compas, char *compas2)
{
	str = ft_substr(str, 2, ft_strlen(str) - 2);
	if (game->we_texture)
		leave(game, str, compas, compas2);
	game->we_texture = ft_strtrim(str, " ");
	game->truc_parse++;
	free(str);
}

void	parse_help5(t_game *game, char *str, char *compas, char *compas2)
{
	str = ft_substr(str, 1, ft_strlen(str) - 1);
	if (game->floor_rgb)
		leave(game, str, compas, compas2);
	game->floor_rgb = ft_strtrim(str, " ");
	game->truc_parse++;
	free(str);
}