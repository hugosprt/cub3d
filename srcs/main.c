#include "../includes/cub.h"

void print_map(char **map)
{
	int i = 0;
	int j = 0;

	while (map[j])
	{
		i = 0;
		while (map[j][i])
		{
			printf("%c", map[j][i]);
			i++;
		}
		printf("\n");
		j++;
	}
}


int	main(int ac, char **av)
{
	t_game	*game;
	char	*str;

	if (ac != 2)
	{
		write(2, "Error\n", 6);
		return (0);
	}
	game = malloc(sizeof(t_game));
	struct_init(game, av[1]);
	str = parse(game);
	game->tab = ft_split(str, '\n');
	free(str);
	//init_img(game, game->tab);
	//print_tiles(game, game->tab);
	//mlx_loop(game->mlx);
	//print_map(game->tab);
	game->tab2 = add_border(game);
	print_map(game->tab2);
	free(game);
	return (0);
} 
