/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouzanb <abouzanb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 23:31:29 by abouzanb          #+#    #+#             */
/*   Updated: 2023/03/05 22:09:28 by abouzanb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int myreadline(char **str)
{
	*str = readline("\nbfbdgsash-3.2$ ");
	if (strcmp(*str, "") == 0)
		return (1);
	if (strlen(*str) > 0)
		add_history(*str);
	return (0);
}

void ft_free(char **str)
{
	int i;
	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
}

void print_export()
{
	t_execute *ptr;
	int		i;

	ptr = g_data.str;
	while (ptr)
	{
		printf("declare -x %s", ptr->name);
		if (ptr->value)
			printf("\"%s\"", ptr->value);
		printf("\n");
		ptr = ptr->next;
	}
	write(1, "\n", 1);
}

int ft_count(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void chnage_old_pwd(char *cmd)
{
	int		i;
	t_execute	*g;

	i = 0;
	g = g_data.str;
	while (g)
	{
		if (strcmp("OLDPWD=", g->name) == 0)
		{
			i = 1;
			free(g->value);
			g->value = cmd;
		}
		if (strcmp("PWD=", g->name) == 0)
		{
			free(g->value);
			g->value = getcwd(NULL, 0);
		}
		g = g->next;
	}
	if (i == 0)
		my_lstadd_back(&g_data.str, my_lstnew(ft_strdup("OLDPWD="), cmd));
}

void fill_env(char **env)
{
	int i;
	char *before;
	char *after;
	i = 0;
	while (env[i])
	{
		before = the_name(env[i]);
		after = the_value(env[i]);
		my_lstadd_back(&g_data.str, my_lstnew(before, after));
		i++;
	}
}