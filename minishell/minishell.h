#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <fcntl.h>
 typedef struct s_s
 {
 	struct s_s	*next;
 	char		*name;
 	char 		*value;
 }t_execute;
typedef struct s_data 
{
	int exit_status;
	int last_exit_status;
	t_execute *str;
}   t_data;

t_data  g_data;

int			ft_isdigit(int a);
size_t		ft_strlen(const char *str);
char		*ft_strdup(const char *s);
int			my_lstsize(t_execute *lst);
t_execute	*my_lstnew(void *before, void *after);
char		*ft_substr(char *str, unsigned int start, size_t len);
char		**ft_split(char *str, char cut);
char		*ft_strjoin(char *str1, char *str2);
int			t_isalnum(int a);
t_execute	*my_lstlast(t_execute *lst);
void		my_lstadd_back(t_execute **lst, t_execute *new);
int			ft_isalpha(int a);
char		*ft_strchr(const char *str, int c);
int			count(char **str);
int			is_no(char *str);
void		ft_echo(char **str);
void		ft_pwd();
int			equal(char *str);
void		fill_env(char **env);
void		ft_env();
int			ft_count(char **str);
void		chnage_old_pwd(char *cmd);
void		ft_cd(char **cmd);
void		print_export();
int			is_valid(char **str);
char		*the_name(char *str);
char		*the_value(char *str);
int			before_is_plus(char *str);
int			update(char *str);
void		add_to_exp(char *str);
int			myreadline(char **str);
void		ft_free(char **str);
void		add_to_export(char **cmd);
void		chnage_old_pwd(char *cmd);
void		ft_export(char **cmd);

#endif