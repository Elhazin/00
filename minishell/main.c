#include "minishell.h"

int main(int ac, char *av[], char *env[])
{
	// char **ptr;
	// char *str;
	// 	int *fds = malloc(sizeof(int) * 2);
	// fds[0] = dup(0);
	// fds[1] = dup(1);

	// fill_env(env);
	// while (1)
	// {
	// while (myreadline(&str) != 0 )
	// 	{
			
	// 	}
	// 	ptr  = ft_split(str,  ' ');
	// 	if (ptr == NULL)
	// 		continue;
	// 	if (strcmp(ptr[0], "echo") == 0)
	// 		ft_echo(ptr);
	// 	else if (strcmp(ptr[0], "cd") == 0)
	// 		ft_cd(ptr);
	// 	else if (strcmp(ptr[0], "env") == 0)
	// 		ft_env();
	// 	else if (strcmp(ptr[0], "pwd") == 0)
	// 		ft_pwd();
	// 	else if (strcmp(ptr[0], "export") == 0)
	// 		ft_export(ptr);
	// 	else 
	// 		system(str);
	// 	dup2(0, fds[0]);
	// 	dup2(1, fds[1]);
	// 	ft_free(ptr);
	// }
	fill_env(env);
	t_exeuction *str = malloc(sizeof(t_exeuction));
	str->str = "cat";

	str->file =NULL;// malloc(sizeof(t_file));
	// str->file->name = "main.c";
	// str->file->type = 'I';
	// str->file->next = NULL;
	t_exeuction *ptr = malloc(sizeof(t_exeuction));
	ptr->str = "cat";
	ptr->file = NULL; /// malloc(sizeof(t_file));
	// ptr->file->name = "ma";
	// ptr->file->type = 'O';
	// ptr->file->next = NULL;
	str->next = ptr; 
	ptr = malloc(sizeof(t_exeuction));
	ptr->str = "ls";
	ptr->file = NULL;
	ptr->next = NULL;

	str->next->next = ptr;
	execution(str);
}

 