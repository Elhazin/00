/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-kadd <hel-kadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 22:36:40 by hel-kadd          #+#    #+#             */
/*   Updated: 2023/03/09 19:28:53 by hel-kadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return ((char *)s + i);
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)s + i);
	return (NULL);
}

size_t ft_strnlen(const char *str, size_t len)
{
	int i;

	i = 0;
	while (str[i] != '\0' && i < len)
		i++;
	return (i);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*s;
	char	*d;
	size_t	i;

	i = 0;
	d = (char *)dst;
	s = (char *)src;
	if (!dst && !src)
		return (NULL);
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dst);
}

char *ft_strndup(const char *s, size_t n)
{
    size_t len;
	char *copy;

    len = ft_strnlen(s, n);
    copy = malloc(len + 1);
    if (copy == NULL)
        return (NULL);
    ft_memcpy(copy, s, len);
    copy[len] = '\0';
    return copy;
}

char	*ft_strdup(const char *src)
{
	size_t	i;
	char	*str;

	i = ft_strlen(src);
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (!str)
	{
		return (0);
	}
	i = 0;
	while (src[i] != '\0')
	{
		str[i] = src[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}