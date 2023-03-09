/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_libft.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouzanb <abouzanb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 21:36:28 by abouzanb          #+#    #+#             */
/*   Updated: 2023/03/06 12:41:52 by abouzanb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strlen(const char *str)
{
	size_t	a;

	a = 0;
	while (str[a] != '\0')
		a++;
	return (a);
}

char	*ft_strdup(const char *s)
{
	char	*str;
	int		i;

	str = (char *)malloc(ft_strlen(s) + 1);
	if (str == NULL)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strjoin(char *str1, char *str2)
{
	int		lenth;
	int		lenth2;
	char	*ptr;

	if (!str1 || !str2)
		return (NULL);
	ptr = (char *)malloc(sizeof(*ptr) * (ft_strlen(str1)+ ft_strlen(str2) + 1));
	if (ptr == NULL)
		return (NULL);
	lenth = 0;
	lenth2 = 0;
	while (str1[lenth] != '\0')
	{
		ptr[lenth] = str1[lenth];
		lenth++;
	}
	while (str2[lenth2] != '\0')
	{
		ptr[lenth] = str2[lenth2];
		lenth++;
		lenth2++;
	}
	ptr[lenth] = '\0';
	return (ptr);
}

int	ft_isalnum(int a)
{
	if ((a <= 90 && a >= 65) || (a <= 122 && a >= 97) || (a <= '9' && a >= '0'))
		return (1);
	return (0);
}

int	ft_isalpha(int a)
{
	if ((a >= 65 && a <= 90) || (a >= 97 && a <= 122))
		return (1);
	return (0);
}

char	*ft_strchr(const char *str, int c)
{
	char	x;
	size_t	l;
	size_t	i;

	x = (char)c;
	i = 0;
	l = ft_strlen(str);
	while (l >= i)
	{
		if (str[i] == x)
		{
			return ((char *)str + i);
		}
		i++;
	}
	return (0);
}

int	is_valid(char **str)
{
	int	i;
	int	j;

	i = 0;

	while (str[i])
	{
		//check_if_the first argumments is null bytes "is nedded here"
		j = 0;
		if (ft_isdigit(str[i][0]) == 1)
			return (0);
		while (str[i] && str[i][j])
		{
			if (str[i][j] == '=')
				return (1);
			if (str[i][j] == '+')
			{
				if (str[i][j + 1] != '=')
					return (0);
			}
			if (ft_isalnum(str[i][j]) == 0 && str[i][j] != '+')
				return (0);
			j++;
		}
			i++;
	}
	return (1);
}

int	ft_lstsize(t_exeuction *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst -> next;
		i++;
	}
	return (i);
}
