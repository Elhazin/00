/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouzanb <abouzanb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 21:33:06 by abouzanb          #+#    #+#             */
/*   Updated: 2023/03/09 18:55:25 by abouzanb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	count(char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

int	is_no(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
		i++;
	while (str[i])
	{
		if (str[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

char *the_name(char *str)
{
	int	i;
	int x;
	char *ptr;

	i = 0;
	x = 0;
	while (str[i])
	{
		if (str[i] == '=')
			break ;
		if (str[i] == '+')
			i++;
		else
		{
			x++;
			i++;
		}
	}
	ptr = malloc(sizeof(char ) * x + 3);
	x = 0;
	i = 0;
	while (str[i])
	{
		ptr[x] = str[i];
		x++;
		i++;
		if (str[i] == '+')
			i++;
		if (str[i] == '=')
		{
					ptr[x] = str[i];
					x++;
			break ;
		}
	}
	//ptr[x] = '=';

	ptr[x] = '\0';
	return (ptr);
}

char *the_value(char *str)
{
	char *ptr;
	int i;
	int a;
	int x;

	x = 0;
	i = 0;

	while (str[i] && str[i] != '=')
		i++;
	
	if (str[i] == '\0')
		return (NULL);
	a = i;
	while (str[a])
		a++;
	ptr = malloc(sizeof(char ) * a + 1);
	if (ptr == NULL)
		return (NULL);
	i++;
	while (str[i])
	{
		ptr[x] = str[i];
		x++;
		i++;
	}
	ptr[x] = '\0';
	return (ptr);
}

int before_is_plus(char *str)
{
	int	i;
	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
		{
			if (str[i - 1] == '+')
				return (1);
			return (0);
		}
		i++;
	}
	return (0);
}
int update(char *str)
{
	t_execute *s;
	char *value;

	s = g_data.str;
	if (before_is_plus(str) != 0)
	{
		while (s)
		{
			if (strcmp(s->name, the_name(str)) == 0)
			{
				s->value = ft_strjoin(s->value, the_value(str));
				return (0);
			}
			s = s->next;
		}
	}
	return (1);
}

int already_is(char *str)
{
	t_execute *s;

	while (s)
	{
		if (strcmp(s->name, the_name(str)) == 0)
		{
			s->value = the_value(str);
			return (0);
		}
		s = s->next;
	}
	return (1);
}

// char every_no_terry(char *str)
// {
	
// }
// int add_to_unvalue(char *str)
// {
// 	t_va va;
// 	va.comd = the_name(str);
// 	if (stch)                                  
// }

void add_to_exp(char *str)
{
	char	*name;
	char	*value;
	int		i;
	int		j;

		
	if (update(str) == 0)
		return ;
	if (already_is(str) == 0)
		return ;
	name = the_name(str);
	value = the_value(str);
	my_lstadd_back(&g_data.str, my_lstnew(name, value));
}
void add_to_export(char **cmd)
{
	int i;
	i = 1;
	if (is_valid(cmd) == 0)
		return ;
	while (cmd[i])
	{
		// 	fprintf(stderr, "ajfhnhjvfd\n");
		// if (cmd[i][0] == '\0')
		// {
		// 	ft_putstr_fd("bash: export: `': not a valid identifier", 2);
		// 	i++;
		// 	continue;
		// }
		add_to_exp(cmd[i]);
		i++;
	}
}

int	equal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (i);
}

