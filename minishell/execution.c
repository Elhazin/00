/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouzanb <abouzanb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 11:20:21 by abouzanb          #+#    #+#             */
/*   Updated: 2023/03/04 15:41:19 by abouzanb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i] != '\0')
	{
		write(fd, "minishell: ", 11);
		write(fd, &s[i], 1);
		i++;
	}
}

void error_print(int i, char *cmd)
{
	if (i == 1)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": command not found", 2);
	}
}
void init(t_va *va)
{
	int i;

	i = 0;
	while(i < (va->size - 1))
		va->fd[i++] = malloc(sizeof(int) * 2);
	i = 0;
	while(i < (va->size - 1))
		pipe(va->fd[i++]);
}
int check_if(t_file *str, char type)
{
	while (str)
	{
		if (str->type == type)
			return (1);
		str = str->next;	
	}
	return (0);
}

void handle_here_doc(t_file *str)
{
	int	fd[2];
	int x;
	int fl;
	char *ptr;
	pipe(fd);
	x = fork();
	if (x == 0)
	{
		while (1)
		{
			ptr = readline("> ");			
			if (memcmp(str->name, ptr, ft_strlen(ptr) - 1) == 0)
			{
				close(fd[1]);
				dup2(fd[0], 0);
				close(fd[0]);
				exit(0);
			}
			write(fd[1], ptr, ft_strlen(ptr));
		}
	}
	close(fd[1]);
	close(fd[0]);
	waitpid(x, 0,0);
}

void handle_input(t_file *file)
{
	int fds;
	fds = open(file->name, O_RDWR, 0777);
	if (fds == -1)
	{
		perror("open");
		exit(1);
	}
	dup2(fds, 0);
	close(fds);
}

void handle_append(t_file *file)
{
	int fds;
	fds = open(file->name, O_CREAT | O_APPEND | O_RDWR, 0777);
	if (fds == -1)
	{
		
		perror("open");
		exit(1);
	}
	dup2(fds, 1);
	close(fds);
}
void	handle_output(t_file *file)
{
	int fds;
	fds = open(file->name, O_CREAT | O_RDWR, 0777);
	if (fds == -1)
	{
		perror("open");
		exit(1);
	}
	dup2(fds, 1);
	close(fds);
}

void handle_other_input(t_exeuction *str, t_va *va)
{
	if (check_if(str->file, 'A') == 0 || check_if(str->file, 'O') == 0)
	{
		if (ft_lstsize(str) > 1)
		{
			dup2(va->fd[va->k][1], 1);
			close(va->fd[va->k][1]);
		}
	}
	if (check_if(str->file, 'H') == 0 || check_if(str->file, 'I') == 0)
	{
		if (ft_lstsize(str) != va->size && va->size != 1)
		{
			dup2(va->fd[va->k][0], 0);
			close(va->fd[va->k][0]);
		}
	}
}
void handle_redir(t_exeuction *str, t_va *va)
{
	t_file *file;

	file = str->file;
	while (file)
	{
		if (file->name)
		{
			if (file->type == 'H')
				handle_here_doc(file);
			else if (file->type == 'I')
				handle_input(file);
			else if (file->type == 'A')
				handle_append(file);
			else if (file->type == 'O')
				handle_output(file);
		}
		file = file->next;
	}
	handle_other_input(str, va);
}

char **get_env()
{
	t_execute	*temp;
	t_va		av;
	char		**env;

	av.i = 0;
	temp = g_data.str;
	av.size = my_lstsize(g_data.str);
	env = malloc(sizeof(char **) * av.size + 1);
	env[av.size] = NULL;
	while (temp)
	{
		env[av.i] = ft_strjoin(temp->name, temp->value);
		temp = temp->next; 
	}
	return (env);
}
int check_if_built(t_exeuction *str)
{
	t_va va;

	va.cmd  = ft_split(str->str, ' ');
	va.i = 0;
	if (strcmp(str->str, "echo") == 0 || strcmp(str->str, "ECHO"))
	{
		ft_echo(va.cmd);
		return (1);
	}
	if (strcmp(str->str, "cd") == 0)
	{
		ft_cd(va.cmd);
		return (1);
	}
	if (strcmp(str->str, "env") == 0 || strcmp(str->str, "ENV") == 0)
	{
		ft_env();
		return (1);
	}
	if (strcmp(str->str, "unset") == 0)
	{
		ft_unset(va.cmd);
		return (1);
	}
	if (strcmp(str->str, "exit") == 0)
	{
		ft_exit(va.cmd);
		return (1);
	}
	if (strcmp(str->str, "export") == 0)
	{
		ft_export(va.cmd);
		return (1);
	}
	if (strcmp(str->str, "pwd") == 0 || strcmp(str->str, "PWD") == 0)
	{
		ft_pwd();
		return (1);
	}
	return (0);
}

void check_the_path(t_exeuction *str, t_va *av, char **path)
{
	int i;

	i = 0;
	while (path[i])
	{
		av->comd = ft_strjoin(path[i], av->cmd[0]);
		if (access(av->comd, X_OK) == 0)
			return ;
		i++;
	}
	av->comd = NULL;
}
void get_path(t_exeuction *str, t_va *av)
{
	t_execute	*tmp;
	char		**path;

	if (access(av->cmd[0], X_OK) == 0)
	{
		av->comd = av->cmd[0];
		return ;
	}
	tmp = g_data.str;
	while (tmp)
	{
		if (tmp->name && strcmp(tmp->name, "PATH=") == 0)
			path = ft_split_with_slash(tmp->value, ':');
		tmp = tmp->next;
	}
	if (path == NULL)
	{
		av->cmd = NULL;
		return ;
	}
	check_the_path(str, av, path);
}
void execute_child(t_exeuction *str, t_va *va)
{
	va->cmd = ft_split(str->str, ' ');
	if (va->cmd == NULL)
		return ;
	handle_redir(str, va);
	if (check_if_built(str) == 0)
	{
		get_path(str, va);
		if (va->comd == NULL)
			error_print(1, str->str);
		va->env = get_env();
		execve(va->comd, va->cmd, va->env);
	}
}

void creates_childs(t_exeuction *str, t_va *va)
{
	int  k;
	 k = 0;
	while (str)
	{
		va->id = fork();
		if (va->id == 0)
		{
			va->k = k;
			execute_child(str, va);
		}
		str = str->next;
		k++;
	}
}
void simple(t_exeuction *str)
{
	
}
void execution(t_exeuction *str)
{
	t_va va;	
	va.size = ft_lstsize(str);
	if (va.size == 0)
		return ;
	if (va.size == 1)
		simple(str);
	else 
	{
		va.fd = malloc(sizeof(int *) * va.size);
		init(&va);
		creates_childs(str, &va);
	}
}
