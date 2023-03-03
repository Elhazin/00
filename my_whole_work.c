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

size_t	ft_strlen(const char *str)
{
	size_t	a;

	a = 0;
	while (str[a] != '\0')
	{
		a++;
	}
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

int	ft_lstsize(t_execute *lst)
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

t_execute	*ft_lstnew(void *before, void *after)
{
	t_execute	*ptr;

	ptr = malloc(sizeof(t_execute));
	if (ptr == NULL)
		return (NULL);
	ptr->name = before;
	ptr->value = after;
	ptr->next = NULL;
	return (ptr);
}
char	*ft_substr(char *str, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	a;
	size_t	lenth;
	size_t	strlenth;

	a = 0;
	if (!str)
		return (NULL);
	strlenth = ft_strlen(str);
	lenth = len;
	if (strlenth < len)
		lenth = strlenth - start;
	if (strlenth < start)
		lenth = 0;
	ptr = (char *)malloc(sizeof(char) * (lenth + 1));
	if (ptr == NULL)
		return (NULL);
	while (a < lenth && str[start])
	{
		ptr[a] = str[start];
		a++;
		start++;
	}
	ptr[a] = '\0';
	return (ptr);
}
static int	strings_count(char *str, char split)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	if (str[i] == '\0')
		return (0);
	while (str[i] == split)
		i++;
	while (str[i])
	{
		if (str[i] != split && (str[i + 1] == split || str[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}
int	ft_isdigit(int a)
{
	if (a <= '9' && a >= '0')
		return (1);
	return (0);
}
static void	helper_function(int x, char cut, char *str, char **ptr)
{
	int	l;
	int	i;
	int	count;

	i = 0;
	count = strings_count(str, cut);
	while (x < count)
	{
		while (str[i] == cut && str[i] != '\0')
		{
			i++;
		}
		if (str[i] != cut && str[i])
		{
			l = i;
			while (str[l] != cut && str[l])
				l++;
			ptr[x] = ft_substr(str, i, (l - i));
			x++;
		}
		while (str[i] && str[i] != cut)
			i++;
	}
}

char	**ft_split(char *str, char cut)
{
	int		x;
	int		count;
	char	**ptr;

	x = 0;
	if (str == NULL)
		return (NULL);
	count = strings_count(str, cut);
	ptr = (char **)malloc(sizeof(char *) * (count + 1));
	if (ptr == NULL)
		return (NULL);
	ptr[count] = NULL;
	helper_function(x, cut, str, ptr);
	return (ptr);
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
t_execute	*ft_lstlast(t_execute *lst)
{
	while (lst)
	{
		if (lst->next == NULL)
		{
			return (lst);
		}
		lst = lst->next;
	}
	return (lst);
}


void	ft_lstadd_back(t_execute **lst, t_execute *new)
{
	t_execute	*ptr;

	if (lst)
	{
		if (*lst)
		{
			ptr = ft_lstlast(*lst);
			ptr->next = new;
		}
		else
			*lst = new;
	}
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

void ft_pwd()
{
	char	str[PATH_MAX];
	
	getcwd(str, sizeof(str));
	printf("%s\n", str);
	g_data.exit_status = 0;
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
void fill_env(char **env)
{
	int i;
	char *before;
	char *after;
	i = 0;
	while (env[i])
	{
		before = ft_substr(env[i], 0, equal(env[i]) + 1);
		after = ft_substr(env[i],  equal(env[i]) - 1, ft_strlen(env[i]));
		ft_lstadd_back(&g_data.str, ft_lstnew(before, after));
		i++;
	}
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
		ft_lstadd_back(&g_data.str, ft_lstnew(ft_strdup("OLDPWD="), cmd));
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

void print_export()
{
	t_execute *ptr;
	int		i;

	ptr = g_data.str;
	while (ptr)
	{
		printf("declare -x %s", ptr->name);
		if (ptr->value)
			printf("\"%s\"\n", ptr->value);
		ptr = ptr->next;
	}
}

int is_valid(char **str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
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
	while (str[i] && str[i] != '=')
	{
		if (str[i] == '+')
			i++;
		ptr[x] = str[i];
		x++;
		i++;
	}
	ptr[x] = '=';
	x++;
	ptr[x] = '\0';
	return (ptr);
}

char *the_value(char *str)
{
	char *ptr;
	int i;
	int x;

	x = 0;
	i = 0;

	while (str[i] && str[i] != '=')
		i++;
	if (str[i] == '\0')
		return (NULL);
	ptr = malloc(sizeof(char ) * i + 1);
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
				printf("%s>>\n", s->value);
				// free(str);
				return (0);
			}
			s =s->next;
		}
	}
	return (1);
}
void add_to_exp(char *str)
{
	char *name;
	char *value;
	int i;
	int j;

	if (update(str) == 0)
		return ;
	name = the_name(str);
	value = the_value(str);
	ft_lstadd_back(&g_data.str, ft_lstnew(name, value));
}
void add_to_export(char **cmd)
{
	int i;

	i = 1;
	if (is_valid(cmd) == 0)
		return ;
	while (cmd[i])
	{
		add_to_exp(cmd[1]);
		i++;
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


int myreadline(char **str)
{
	*str = readline("bash-3.2$ ");
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
// int check_is_there(char *str)
// {
// 	int i;
// 	t_execute *ptr;

// 	if (str == NULL)
// 		return (0);
// 	ptr = g_data.str; 
// 	i = 0;
// 	while (ptr)
// 	{
// 		if (strcmp(ptr->name, str) == 0)
// 			return (1);
// 		if (strcmp(ptr->name, ft_split(str, '=')))
// 	}
	
// }

// void ft_unset(char **str)
// {
// 	int k;
// 	int i;
// 	i  = 1;
// 	t_execute *ptr;
// 	ptr  = g_data.str;
// 	if (ft_count(str) == 0 || ft_count(str) == 1)
// 		return (0);
// 	while (str[i])
// 	{
// 		k = check_if_there(the_name(str[i]));
// 		if (k == 0)
// 		{
// 			i++;
// 			continue;
// 		}
// 		unset_it(str[i]);
// 		i++;
// 	}
// }
int main(int ac, char *av[], char *env[])
{
	char **ptr;
	char *str;
		int *fds = malloc(sizeof(int) * 2);
	fds[0] = dup(0);
	fds[1] = dup(1);

	fill_env(env);
	while (1)
	{
		while (myreadline(&str) != 0 )
		{
			
		}
		ptr  = ft_split(str,  ' ');
		free(str);
		if (ptr == NULL)
			continue;
		if (strcmp(ptr[0], "echo") == 0)
			ft_echo(ptr);
		else if (strcmp(ptr[0], "cd") == 0)
			ft_cd(ptr);
		else if (strcmp(ptr[0], "env") == 0)
			ft_env();
		else if (strcmp(ptr[0], "pwd") == 0)
			ft_pwd();
		else if (strcmp(ptr[0], "export") == 0)
			ft_export(ptr);
		else 
			system(str);
		dup2(0, fds[0]);
		dup2(1, fds[1]);
		ft_free(ptr);
	}
}