/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouzanb <abouzanb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 11:20:21 by abouzanb          #+#    #+#             */
/*   Updated: 2023/03/12 19:18:07 by abouzanb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_close(t_va *va, t_exeuction *str)
{
	int	i;

	i = 0;
	if (va->k != 0)
	{
		printf("%d\n", va->k);
		close(va->fd[va->k - 1][0]);
		close(va->fd[va->k - 1][1]);
	}
	if (ft_lstsize(str) == 1)
	{
		close(va->fd[va->k - 1][0]);
		close(va->fd[va->k - 1][1]);
	}
}

void my_close(t_va *va)
{
	int i  = 0;
	while (i < va->size - 1)
	{
		close(va->fd[i][0]);
		close(va->fd[i][1]);
		i++;
	}
	
}
void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	write(fd, "minishell: ", 11);
	while (s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
	}
	write(fd, "\n", 1);
}

void error_print(int i, char *cmd)
{
	if (i == 1)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": command not found", 2);
		exit(127);
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
	fprintf(stderr, "aloha aloha\n");
	pipe(fd);
	x = fork();
	if (x == 0)
	{
		while (1)
		{
			ptr = readline("> ");
			if (ptr == NULL)
				exit (1);
			if (memcmp(str->name, ptr, ft_strlen(ptr)) == 0)
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
			if (ft_lstsize(str) == va->size)
			{
				close(va->fd[va->k][0]);
			}
			dup2(va->fd[va->k][1], 1);
			close(va->fd[va->k][1]);
		}
	}
	if (check_if(str->file, 'H') == 0 || check_if(str->file, 'I') == 0)
	{
		if (ft_lstsize(str) != va->size && va->size != 1)
		{
			close(va->fd[va->k - 1][1]);
			dup2(va->fd[va->k - 1][0], 0);
			close(va->fd[va->k - 1][0]);
		}

	}
}

void read_from_here_doc(t_file *file)
{
	while (file)
	{
		if (file->type == 'H')
			handle_here_doc(file);
		file = file->next;
	}
}
void handle_redir(t_exeuction *str, t_va *va)
{
	t_file *file;

	file = str->file;
	read_from_here_doc(file);
	while (file)
	{
		if (file->name)
		{
			 if (file->type == 'I')
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

int	my_lstsize(t_execute *lst)
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
	while (av.i < av.size)
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
	if (strcmp(str->str, "echo") == 0 || strcmp(str->str, "ECHO") == 0)
	{
		ft_echo(va.cmd);
		return (1);
	}
	else if (strcmp(str->str, "cd") == 0)
	{
		ft_cd(va.cmd);
		return (1);
	}
	else if (strcmp(str->str, "env") == 0 || strcmp(str->str, "ENV") == 0)
	{
		ft_env();
		return (1);
	}
	else if (strcmp(str->str, "unset") == 0)
	{
		ft_unset(va.cmd);
		return (1);
	}
	else if (strcmp(str->str, "exit") == 0)
	{
		ft_exit(va.cmd);
		return (1);
	}
	else if (strcmp(str->str, "export") == 0)
	{
		ft_export(va.cmd);
		return (1);
	}
	else if (strcmp(str->str, "pwd") == 0 || strcmp(str->str, "PWD") == 0)
	{
		ft_pwd();
		return (1);
	}
	return (0);
}

void check_the_path(t_exeuction *str, t_va *av, char **path)
{
	int	i;

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
		//va->env = get_env();
		my_close(va);
		execve(va->comd, va->cmd, NULL);
		perror("execve");
	}
}

void creates_childs(t_exeuction *str, t_va *va)
{
	int	k;

	va->k = 0;
	va->i = 0;
	while (str)
	{
		va->id = fork();
		if (va->id == 0)
		{
			execute_child(str, va);
		}
		ft_close(va, str);
		str = str->next;
		(va->k)++;
	}
}

void	simple(t_exeuction *str, t_va *av)
{
	av->size = 1;
	av->cmd = ft_split(str->str, ' ');
	handle_redir(str, av);
	if (check_if_built(str) == 0)
	{
		av->id = fork();
		if (av->id == 0)
		{
			get_path(str, av);
			if (av->comd == NULL)
				error_print(1, str->str);
		//	av->env = get_env();
			execve(av->comd, av->cmd,NULL);
		}
	}
	ft_free(av->cmd);
}

void wait_for_them(t_va *va)
{
	int i;
	int status;
	
	i = 0;
	while (i < va->size)
	{
		if (waitpid(-1, &status, 0) == 0)
			g_data.exit_status = status;
		i++;
	}
}
void execution(t_exeuction *str)
{
	t_va va;	
	va.size = ft_lstsize(str);
	if (va.size == 0)
		return ;
	if (va.size == 1)
	{
		simple(str, &va);
		wait_for_them(&va);
	}
	else
	{
		va.fd = malloc(sizeof(int *) * va.size - 1);
		init(&va);
		creates_childs(str, &va);
		wait_for_them(&va);
		my_close(&va);
	}
}
