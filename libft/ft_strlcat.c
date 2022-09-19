/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpol <rpol@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 02:29:25 by rpol              #+#    #+#             */
/*   Updated: 2022/02/10 23:53:05 by rpol             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

size_t	ft_strlcat(char *dest, const char *src, size_t len)
{
	size_t	i;
	size_t	lendnd;
	size_t	lens;

	i = 0;
	lendnd = 0;
	lens = strlen((char *)src);
	if (len == 0)
		return (lens);
	while (dest[lendnd] && lendnd < len)
		lendnd++;
	if (len == lendnd)
		return (len + lens);
	while (lendnd + i < len - 1 && src[i])
	{
		dest[i + lendnd] = src[i];
		i++;
	}
	dest[i + lendnd] = '\0';
	return (lendnd + lens);
}
