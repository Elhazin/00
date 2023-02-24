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
 typedef struct s_files
 {
	char *name;
	char type;
	struct  s_files *next;
 }t_file;
typedef struct  s_list
{
	char			*str;
	t_file 			*file;
	int				i;
	int				k;
	struct  s_list	*next;
}t_list;

char	*ft_substr(char const *str, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	a;
	size_t	lenth;
	size_t	strlenth;

	a = 0;
	if (!str)
		return (NULL);
	strlenth = strlen(str);
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

int	ft_lstsize(t_list *lst)
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
void handle_here_doc(t_file *str)
{

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
int check_it(t_file *str, char type)
{
	while (str)
	{
		if (str->type == type)
			return (1);
		str = str->next;
	}
	return (0);
}
void handle_no_input(t_list *str, int fd[][2])
{
	if (check_it(str->file, 'A') == 0 || check_it(str->file, 'O') == 0)
	{
		if (ft_lstsize(str) > 1)
		{
			dup2(fd[str->k][1], 1);
			close(fd[str->k][1]);
		}
	}
	if (check_it(str->file, 'I') == 0 || check_it(str->file, 'H') == 0)
	{
		if (ft_lstsize(str) != str->i)
		{
			dup2(fd[str->k - 1][0], 0);
			close(fd[str->k - 1][0]);
		}
	}
}
void	handle_redir(t_list *str, int fd[][2], int i)
{
	t_file *file;

	file = str->file;
	if (str->file != NULL)
	{
		while (file)
		{
			if (file->name != NULL)
			{
				if (file->type == 'H')
					handle_here_doc(file);
				else if (file->type == 'I')
					handle_input(file);
				else if (file->type == 'O')
					handle_output(file);
				else if (file->type == 'A')
					handle_append(file);
			}
			file = file->next;
		}
	}
	handle_no_input(str, fd);
}
void execute_chile(t_list *str, int fd[][2], int i, int k)
{
	char **ptr = ft_split(str->str, ' ');
	str->k = k;
	handle_redir(str, fd, i);
	int temp = k;
	while (temp)
	{
		close(fd[k - temp][0]);
		close(fd[k - temp][1]);
		temp--;
	}
	execve(ptr[0], ptr, NULL);	
	perror("execve");
}

void execute(t_list *str)
{
	int fd[ft_lstsize(str) - 1][2];
	int i  = ft_lstsize(str);
	int k = 0;
	int h = 0;
	while (h < i)
		pipe(fd[h++]);
	while (str)
	{
		if (fork() == 0)
		{
			str->i = i;
			execute_chile(str, fd, i, k);
		}
		str = str->next;
		k++;
	}
	if (i > 1)
	{
	close(fd[0][1]);
	close(fd[0][0]);
	}
	wait(NULL);
}
int main()
{
	t_list *str;
	t_list *ptr;
	str = malloc(sizeof(t_list));
	str->file = malloc(sizeof(t_file));
	// str->in = NULL;
	str->file->name = "test.c";
	str->file->type = 'I';
	str->file->next = NULL;
	str->str = "/bin/cat";
	// str->next = NULL;
	ptr = malloc(sizeof(t_list));
	ptr->file = malloc(sizeof(t_file));
	str->next = ptr;
	ptr->file->name = "out";
	ptr->file->type = 'O';
	ptr->file->next = malloc(sizeof(t_file));
	ptr->file->next->name = "out2";
	ptr->file->next->type = 'O';
	ptr->file->next->next = NULL;
	ptr->str = "/usr/bin/wc";
	ptr->next = NULL;
	// ptr = malloc(sizeof(t_list));
	// str->next = ptr;
	// ptr->in = NULL;
	// ptr->next = NULL;
	// ptr->out = "OPLA";
	// ptr->str = "/usr/bin/wc";
	// ptr = malloc(sizeof(t_list));
    // str->next->next = ptr;
	// ptr->in = "test.c";
	// ptr->next = NULL;
	// ptr->out = "OPLA";
	// ptr->str = "/bin/cat";
	// str->next->next = ptr;
	execute(str);
}