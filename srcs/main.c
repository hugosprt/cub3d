#include "../includes/cub.h"

void print_map(t_game *game)
{
	int i = 0;
	int j = 0;
	while (game->tab3[j])
	{
		i = 0;
		while (game->tab3[j][i])
		{
			printf("%c", game->tab3[j][i]);
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
	parse_settings(game);
	game->tab3 = final_map(game);
	printf("texture nord |%s| \ntexture sud |%s| \ntexture west |%s| \ntexture east |%s| \ncouleur sol |%s| \ncouleur ciel |%s| \n" , game->NO_texture, game->SO_texture, game->WE_texture ,game->EA_texture, game->floor_rgb,game->ceiling_rgb);
	print_map(game);
	free(game);
	return (0);
} 
