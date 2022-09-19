/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hspriet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 14:28:07 by hspriet           #+#    #+#             */
/*   Updated: 2022/01/05 15:54:26 by hspriet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"
#include "../../includes/cub.h"

int	ft_strlen_buff(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != '\n')
		i++;
	return (i);
}

int	ft_strlen2(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*s3;
	int		i;
	int		j;

	if (s1 == NULL)
	{
		s1 = malloc(1 * (sizeof (char)));
		s1[0] = 0;
	}
	s3 = malloc(1 + (ft_strlen(s1) + ft_strlen(s2)) * (sizeof (char)));
	if (s3 == NULL)
		return (NULL);
	i = ((j = 0), 0);
	while (s1[i] && s1)
	{
		s3[i] = s1[i];
		i++;
	}
	while (s2[j] && s2)
	{
		s3[i + j] = s2[j];
		j++;
	}
	s3[ft_strlen(s1) + ft_strlen(s2)] = '\0';
	return (free(s1), s3);
}

char	*ft_substr(char *s, int start, int len)
{
	int		i;
	char	*new;

	i = 0;
	if (!s)
		return (NULL);
	if (ft_strlen(s) <= start)
		len = 0;
	if (ft_strlen(s) <= len)
		len = ft_strlen(s);
	new = malloc(sizeof(char) * (len + 1));
	if (!new)
		return (NULL);
	while (s[i + start] && i < len)
	{
		new[i] = s[i + start];
		i++;
	}
	new[i] = '\0';
	return (new);
}

char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
		{
			return ((char *)(s + i));
		}
		i++;
	}
	if (c == '\0')
		return ((char *)(s + i));
	return (NULL);
}
