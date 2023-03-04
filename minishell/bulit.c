/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bulit.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouzanb <abouzanb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 21:45:38 by abouzanb          #+#    #+#             */
/*   Updated: 2023/03/04 15:32:48 by abouzanb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_unset(char **str)
{
	
}
void ft_exit(char **str)
{
	
}
void	ft_echo(char **str)
{
	int	i;
	int	x;

	i = 1;
	x = 0;
	if (count(str) > 1)
	{
		while (str[i] && str[i][0] && is_no(str[i]) == 0)
		{
			x++;
			i++;
		}
		while (str[i])
		{
			printf("%s", str[i]);
			if (str[i + 1])
				printf(" ");
			i++;
		}
		if (x == 0)
			printf("\n");
	}
	g_data.exit_status = 0;
}

void	ft_env()
{
	t_execute	*temp;
	temp = g_data.str;
	while (temp)
	{
		if (ft_strchr(temp->name , '=') != NULL)
		{
			printf("%s",temp->name);
			if (temp->value != NULL)
				printf("%s\n",temp->value);
		}
		temp = temp->next;
	}
	g_data.exit_status = 0;
}

void ft_cd(char **cmd)
{
	int	i;
	char *pwd;

	i = 0;
	pwd = getcwd(NULL, 0);
	if (ft_count(cmd) == 1)
	{
		chdir("/Users/abouzanb");
		chnage_old_pwd(pwd);
	}
	else
	{
		if (chdir(cmd[1]) == -1)
			printf("bash: cd: %s: No such file or directory\n", cmd[1]);
		chnage_old_pwd(pwd);
	}
}

void ft_export(char **cmd)
{
	if (ft_count(cmd) == 1)
	{
		print_export();
		g_data.exit_status = 0;
	}
	else
		add_to_export(cmd);
}

void ft_pwd()
{
	char	str[PATH_MAX];
	
	getcwd(str, sizeof(str));
	printf("%s\n", str);
	g_data.exit_status = 0;
}

