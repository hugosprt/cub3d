/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpol <rpol@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 13:49:44 by rpol              #+#    #+#             */
/*   Updated: 2022/02/07 16:13:02 by rpol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_strchr(char *s, char c)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(s);
	while (i <= len)
	{
		if (s[i] == c)
			return (0);
		i++;
	}
	return (1);
}

int	ft_strlen(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	char	*news;

	i = 0;
	news = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!news)
		return (NULL);
	while (i < (ft_strlen(s1) + ft_strlen(s2)))
	{
		if (i < ft_strlen(s1))
			news[i] = s1[i];
		else
			news[i] = s2[(i - ft_strlen(s1))];
		i++;
	}
	news[i] = '\0';
	free(s1);
	return (news);
}

char	*ft_line(char *s)
{
	char	*tmp;
	int		i;
	int		n;

	i = 0;
	n = 0;
	if (!s)
		return (NULL);
	while (s[i] && s[i] != '\n')
		i++;
	if (s[i] == '\n')
		n = 1;
	tmp = malloc(sizeof(char) * (i + 1 + n));
	if (!tmp)
		return (NULL);
	tmp[i + n] = '\0';
	if (n == 1)
		tmp[i] = '\n';
	i = 0;
	while (s[i] && s[i] != '\n')
	{
		tmp[i] = s[i];
		i++;
	}
	return (tmp);
}

char	*ft_cut(char *s, char *line)
{
	char	*cut;
	int		i;
	int		j;

	if ((ft_strlen(s) == ft_strlen(line)) || !line)
	{
		free(s);
		return (NULL);
	}
	i = 0;
	while (s[i] != '\n')
		i++;
	cut = malloc(sizeof(char) * (ft_strlen(s) + 1 - i));
	if (!cut)
	{
		free(s);
		return (NULL);
	}
	j = 0;
	while (s[i])
		cut[j++] = s[++i];
	free(s);
	return (cut);
}
