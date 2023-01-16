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
    int j;
    int size;

    size = 0;
    i = 0;
    j = 0;

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

int add_value(t_game *game, char *str)
{
	int i;
	char **tab;
	int nb_color;
	int texure;

	(void) game ;
	texure = 0;
	nb_color = 0;
	i = 0;
	tab = ft_split(str, ' ');
	while (tab[i])
	{
		if (ft_strcmp(tab[i], "NO") == 0)
		{
			game->NO_texture = ft_strdup(tab[i + 1]);
			texure++;
		}
		else if (ft_strcmp(tab[i], "SO") == 0)
		{
			game->SO_texture = ft_strdup(tab[i++]);
			texure++;
		}
		else if (ft_strcmp(tab[i], "WE") == 0)
		{
			game->WE_texture = ft_strdup(tab[i++]);
			texure++;
		}
		else if (ft_strcmp(tab[i], "EA") == 0)
		{
			game->EA_texture = ft_strdup(tab[i++]);
			texure++;
		}
		else if (ft_strcmp(tab[i], "F") == 0)
		{
			while(ft_strcmp(tab[i], ",") || ft_isnum(tab[i]))
			{
				game->floor_rgb = ft_strjoin(tab[i], ",");
				i++;
			}
		}
		else if (ft_strcmp(tab[i], "C") == 0)
		{
			while(ft_strcmp(tab[i], ",") || ft_isnum(tab[i]))
			{
				game->ceiling_rgb = ft_strjoin(tab[i], ",");
				i++;
			}
		}
		i++;
	}
	return (0);
}

void	struct_init(t_game *game, char *file)
{
	game->x = 0;
	game-> truc_parse = 0;
	game->texture =0;
	game->y = 0;
	game->is_player = 1;
	game->is_valid = 1;
	game->fd = open(file, O_RDONLY);
}


