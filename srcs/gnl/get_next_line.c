/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hspriet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 11:49:28 by hspriet           #+#    #+#             */
/*   Updated: 2022/01/05 15:47:24 by hspriet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "../../includes/cub.h"

char	*get_next_line(int fd)
{
	static char	*str = NULL;
	char		*buff;
	char		*ret;
	int			f;
	char		*str2;

	f = 1;
	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	buff = (char *) malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	while (! (ft_strchr(str, '\n')) && f)
	{
		f = read(fd, buff, BUFFER_SIZE);
		if (f == -1 || (f == 0 && ft_strlen(str) == 0))
			return (free(str), free(buff), NULL);
		buff[f] = '\0';
		str = ft_strjoin(str, buff);
	}
	str2 = str;
	ret = ft_substr(str, 0, ft_strlen_buff(str) + 1);
	str = ft_substr(str, ft_strlen(ret), ft_strlen(str) - ft_strlen(ret) + 1);
	return (free(str2), free(buff), ret);
}
