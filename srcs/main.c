#include "../includes/cub.h"

int	main(int ac, char **av)
{
	t_game *game;

	(void) ac;
	(void) av;
	game = malloc((sizeof (t_game)));
	if (ac != 2)
		parse_error();
	game->mlx = mlx_init();
	if (game->mlx == NULL)
		parse_error();
	parse(av[1], game);
} 
