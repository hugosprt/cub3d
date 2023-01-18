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

int     find_longer_line(char   **map)
{
    int i;
    int j;
    int size;

    size = 0;
    i = 0;
    j = 0;

    while (map[i])
    {
        j = ft_strlen(map[i]);
        if (j > size)
            size = j;
        i++;
    }
    return (size);
}

int     find_longer_collum(char   **map)
{
    int i;

    i = 0;

    while (map[i])
    {
        i++;
    }
    return (i);
}
char	*ft_strjoin4(char const *s1, char const *s2)
{
	char	*s3;
	int		len;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	s3 = (char *) malloc(1 + len * (sizeof (char)));
	if (s3 == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		s3[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		s3[i + j] = s2[j];
		j++;
	}
	s3[i + j] = '\0';
	return (s3);
}
char **add_border(t_game *game)
{
    int k;
    int j;
    char *str;
    char **new_map;

    j = 0;
    new_map = malloc(sizeof(char **) * (find_longer_collum(game->tab)));
    while (j < find_longer_collum(game->tab))
    {
        k = 0;
        str = ft_strdup(game->tab[j]);
        new_map[j] = ft_strdup(str);
        k = ft_strlen(str);
        while (k < find_longer_line(game->tab))
        {
            new_map[j] = ft_strjoin4(new_map[j], " ");
            k++;
        }
        j++;
    }
    return (new_map);    
}

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
	return (free(tmp), tab);
}

int	ft_isnum(char *str)
{
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
			return (1);
		str++;
	}
	return (0);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while ((s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)(s1[i]) - (unsigned char)(s2[i]));
		i++;
	}
	return (0);
}

char	*ft_strldup(char *source, int size)
{
	char	*dest;
	int		len;
	int		i;

	if (!source)
		return (NULL);
	i = 0;
	len = ft_strlen(source);
	dest = (char *) malloc(1 + len * sizeof(char));
	if (dest == NULL)
		return (NULL);
	while (i < len && i != size)
	{
		dest[i] = source[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

void parse_settings(t_game *game)
{
	char 	**tab;
	char 	*str;
	char	*compas = NULL;
	char *compas2 = NULL;
	int		i = 0;

	tab = game->tab2;
	while(tab[i])
	{
		str = ft_strtrim(tab[i], " ");
		if (!str)
			throw_error3(game, *tab);
		if (ft_strlen(str) <= 4)
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
			if (game->NO_texture)
				throw_error3(game, *tab);
			game->NO_texture = ft_strtrim(str, " ");
			game->truc_parse++;
		}
		else if (!ft_strcmp(compas, "SO"))
		{
			str = ft_substr(str, 2, ft_strlen(str) - 2);
			if (game->SO_texture)
				throw_error3(game, *tab);
			game->SO_texture = ft_strtrim(str, " ");
			game->truc_parse++;
		}
		else if (!ft_strcmp(compas, "WE"))
		{
			str = ft_substr(str, 2, ft_strlen(str) - 2);
			if (game->WE_texture)
				throw_error3(game, *tab);
			game->WE_texture = ft_strtrim(str, " ");
			game->truc_parse++;
		}
		else if (!ft_strcmp(compas, "EA"))
		{
			str = ft_substr(str, 2, ft_strlen(str) - 2);
			if (game->EA_texture)
				throw_error3(game, *tab);
			game->EA_texture = ft_strtrim(str, " ");
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
	}
	
}

char	**final_map(t_game *game)
{
	int k;
    int j;
    char *str;
    char **new_map;

    j = 6;
    new_map = malloc(sizeof(char **) * (find_longer_collum(game->tab) - 6));
    while (j < find_longer_collum(game->tab2))
    {
        k = 0;
		if (!ft_isdigit(game->tab2[j][0]) && game->tab2[j][0] != ' ')
		{
			printf("%c\n", game->tab2[j][0]);
			throw_error3(game, *new_map);
		}
        str = ft_strdup(game->tab2[j]);
        new_map[j - 6] = ft_strdup(str);
        k = ft_strlen(str);
        while (k < find_longer_line(game->tab2))
        {
            new_map[j] = ft_strjoin4(new_map[j], " ");
            k++;
        }
        j++;
    }
	return (new_map);


}


void	struct_init(t_game *game, char *file)
{
	game->x = 0;
	game->NO_texture = NULL;
	game->SO_texture = NULL;
	game->EA_texture = NULL;
	game->WE_texture = NULL;
	game->floor_rgb = NULL;
	game->ceiling_rgb = NULL;
	game-> truc_parse = 0;
	game->texture =0;
	game->y = 0;
	game->is_player = 1;
	game->is_valid = 1;
	game->fd = open(file, O_RDONLY);
}


