#include "../../includes/cub.h"
void	free_magic(t_game *g)
{
	int i;
	i=0;
	while (g->tab[i] != NULL)
	{
		free(g->tab[i]);
		i++;
	}
	free(g->tab);
	i= 0;
	while (g->tab2[i] != NULL)
	{
		free(g->tab2[i]);
		i++;
	}
	free(g->tab2);
	i = 0;
	while (g->tab3[i] != NULL)
	{
		free(g->tab3[i]);
		i++;
	}
	free(g->tab3);
}
void free_tab(char **tab)
{
	int i;
	i=0;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}


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

void	throw_error4(t_game *game)
{
	ft_printf("error map2\n");
	free(game);
	exit(EXIT_FAILURE);
}

void	throw_error66(t_game *game)
{
	ft_printf("on gere pas les pipes dans minishell t'as cru on allait faire un multi??\n");
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

void add_border(t_game *game)
{
    int k;
    int j;
    char *str;
	char *str2;

    j = 0;
    game->tab2 = malloc(sizeof(char **) * (find_longer_collum(game->tab) + 1));
    while (j < find_longer_collum(game->tab))
    {
        k = 0;
        str = ft_strdup(game->tab[j]);
        game->tab2[j] = ft_strdup(str);
        k = ft_strlen(str);
		free(str);
        while (k < find_longer_line(game->tab))
        {
			str2 = game->tab2[j];
			str = ft_strjoin4(str2, " ");
            game->tab2[j] = str;
			free(str2);
            k++;
        }
        j++;
    }
	game->tab2[j] = NULL;   
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
	char 	*str = NULL;
	char	*compas = NULL;
	char	*compas2 = NULL;
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
		free(compas2);
		free(compas);
		free(str);
	}
	free(compas2);
	free(compas);
}

void	final_map(t_game *game)
{
	int k;
    int j;
    char *str = NULL;
	char *str2;

	
    j = 6;
	game->tab3 = malloc(sizeof(char **) * (find_longer_collum(game->tab) - 5));
	if (!game->tab3)
		return ;
    while (j <  find_longer_collum(game->tab2))
    {
        k = 0;
        str = ft_strdup(game->tab2[j]);
		if (!str)
			throw_error3(game, str);
        game->tab3[j - 6] = ft_strdup(str);
        k = ft_strlen(str);
		free(str);
		str = NULL;
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

void is_collunm_top(t_game *game)
{
	int i;
	int j;
	int	size;

	size = find_longer_line(game->tab3);
	i = 0;
	j = 0;
	while(j != size)
	{
		i = 0;
		while (game->tab3[i][j] != '1')
		{
			if (game->tab3[i][j] != ' ')
				throw_error4(game);
			i++;
		}
		j++;
	}
}

void is_collunm_bot(t_game *game)
{
	int i;
	int j;
	int	size;
	int s2;
	
	size = find_longer_line(game->tab3);
	s2 = find_longer_collum(game->tab3);
	i = 0;
	j = 0;
	while(j != size)
	{
		i = 1;
		while (game->tab3[s2 - i][j] != '1')
		{
			if (game->tab3[s2 - i][j] != ' ')
				throw_error4(game);
			i++;
		}
		j++;
	}
}

void	is_line_left(t_game *game)
{
	int i; 
	int j;

	i = 0;
	j = 0;

	while (game->tab3[j])
	{
		i = 0;
		while (game->tab3[j][i] != '1')
		{
			// printf("%c\n",game->tab3[j][i]);
			// printf("i : %d  j : %d\n", i , j);
			if (game->tab3[j][i] != ' ')
			{
				// printf("here\n");
				throw_error4(game);
			}
			i++;
		}
		j++;
	}
}

void	is_line_right(t_game *game)
{
	int i; 
	int j;
	int size;

	size = find_longer_line(game->tab3);

	i = 0;
	j = 0;
	while (game->tab3[j])
	{
		i = 1;
		while (game->tab3[j][size - i] != '1')
		{
			if (game->tab3[j][size - i] != ' ')
			{
				// printf("here\n");
				throw_error4(game);
			}
			i++;
		}
		j++;
	}
}

int check_zero(t_game *game, int i, int j)
{
	if (!game->tab3[j][i + 1]  || game->tab3[j][i + 1] == ' ')
		return (0);
	if (!game->tab3[j][i - 1]  || game->tab3[j][i - 1] == ' ')
		return (0);
	if (!game->tab3[j - 1][i]  || game->tab3[j - 1][i] == ' ')
		return (0);
	return (1);
}

void	if_zero(t_game *game, char **tab3)
{
	int i; 
	int j;

	i = 0;
	j = 0;
	while (tab3[j])
	{
		i = 0;
		while (tab3[j][i])
		{
			// printf("%c\n",game->tab3[j][i]);
			// printf("i : %d  j : %d\n", i , j);
			if (tab3[j][i] == '0')
			{
				if (!check_zero(game, i, j))
				{
					throw_error4(game);
				}
			}
			i++;
		}
		j++;
	}
}

void	is_player(t_game *game)
{
	int i; 
	int j;
	char **tab3;

	i = 0;
	j = 0;
	tab3 = game->tab3;
	while (tab3[j])
	{
		i = 0;
		while (tab3[j][i])
		{
			if (tab3[j][i] == 'N' || tab3[j][i] == 'S' || tab3[j][i] == 'E' || tab3[j][i] == 'W')
			{
				if (game->is_player != 'H')
					throw_error66(game);
				if (!check_zero(game, i, j))
				{
					throw_error4(game);
				}
				game->is_player = tab3[j][i];
			}
			i++;
		}
		j++;
	}
}

int check_valid_input(const char* s, int* r, int* g, int* b) {
    int i = 0, j = 0, k = 0, l = 0;
    while (s[i] != ',' && s[i] != '\0') {
        if (ft_isdigit(s[i])) {
            *r = (*r * 10) + (s[i] - '0');
            j++;
        }
        else {
            return -1;
        }
        i++;
    }
    if (s[i] == '\0' || j==0) {
        return -1;
    }
    i++;
    while (s[i] != ',' && s[i] != '\0') {
        if (ft_isdigit(s[i])) {
            *g = (*g * 10) + (s[i] - '0');
            k++;
        }
        else {
            return -1;
        }
        i++;
    }
    if (s[i] == '\0' || k==0) {
        return -1;
    }
    i++;
    while (s[i] != '\0') {
        if (ft_isdigit(s[i])) {
            *b = (*b * 10) + (s[i] - '0');
            l++;
        }
        else {
            return -1;
        }
        i++;
    }
    if(j==0 || k==0 || l==0) return -1;
    return 0;
}
int parse_rgb_color(t_game *game, char *s) {
    int r = 0, g = 0, b = 0;
    if(check_valid_input(s,&r,&g,&b) == -1){
        throw_error4(game);
    }
    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255) {
        throw_error4(game);
    }
    return (r << 16) | (g << 8) | b;

}

void main_parsing(t_game *game)
{
	char *str;
//	char **temp;

	str = parse(game);
	game->tab = ft_split(str, '\n');
	free(str);
	add_border(game);
	parse_settings(game);
//	printf("texture nord |%s| \ntexture sud |%s| \ntexture west |%s| \ntexture east |%s| \ncouleur sol |%s| \ncouleur ciel |%s| \n" , game->NO_texture, game->SO_texture, game->WE_texture ,game->EA_texture, game->floor_rgb,game->ceiling_rgb);
	final_map(game);
	if_zero(game, game->tab3);
	is_collunm_top(game);
	is_collunm_bot(game);
	is_line_left(game);
	is_line_right(game);
	is_player(game);
	game->sky_color = parse_rgb_color(game, game->ceiling_rgb);
	game->ground_color = parse_rgb_color(game, game->floor_rgb);
}

