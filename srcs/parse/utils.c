#include "../../includes/cub.h"

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

int	find_longer_collum(char	**map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}
