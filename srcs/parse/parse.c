#include "../../includes/cub.h"


void	throw_error(t_game *game, char *tab)
{
	ft_printf("error fd\n");
	free(tab);
	free(game);
	exit(EXIT_FAILURE);
}

void	throw_error2(t_game *game, char *tab)
{
	ft_printf("error no map\n");
	free(tab);
	free(game);
	exit(EXIT_FAILURE);
}

void	throw_error3(t_game *game, char *tab)
{
	ft_printf("error map\n");
	free(tab);
	free(game);
	exit(EXIT_FAILURE);
}

void	check_error(t_game *game, char *tab)
{
	if (game->is_player != 'N'  || game->is_valid != 1)
		throw_error3(game, tab);
}



void	mid(t_game *game, char *av)
{
	int	i;

	i = 0;
	while (av[i] && av[i] != '\n')
	{
		if ((av[i] != '1' && i == 0) || (av[i] != '1' && (i == ft_strlen(av) - 2)))
        {
			game->is_valid = 2;
        }
		if (av[i] == 'N')
			game->is_player = av[i];
		else if (av[i] != '0' && av[i] != '1')
        		game->is_valid = 9;
		i++;
	}
}

void	firstlast(t_game *game, char *av)
{
	int	i;

	i = 0;
	while (av[i] != '\n' && av[i])
	{
		if (av[i] != '1')
			game->is_valid = 0;
		i++;
	}
}

// char **add_border(t_game *game)
// {

// }

char	*parse(t_game *game)
{
	char		*ret;
	char		*tmp;
	char		*tab;
    int         i;

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
		tmp = ret;
		i++;
		ret = get_next_line(game->fd);
		if (ret != NULL)
			free(tmp);
	}
	return (free(tmp), check_error(game, tab), tab);
}

void	struct_init(t_game *game, char *file)
{
	game->x = 0;
	game->y = 0;
	game->is_player = 0;
	game->is_valid = 1;
	game->fd = open(file, O_RDONLY);
}


