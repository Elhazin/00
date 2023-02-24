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
void handle_here_doc(t_list *str)
{

}
void handle_input(t_list *str)
{
	int fds;
	fds = open(str->file->name, O_RDWR, 0777);
	if (fds == -1)
	{
		perror("open");
		exit(1);
	}
	dup2(fds, 0);
	close(fds);
}
void handle_append(t_list *str)
{
	int fds;
	fds = open(str->file->name, O_CREAT | O_APPEND | O_RDWR, 0777);
	if (fds == -1)
	{
		perror("open");
		exit(1);
	}
	dup2(fds, 1);
	close(fds);
}
void	handle_output(t_list *str)
{
	int fds;
	fds = open(str->file->name, O_CREAT | O_RDWR, 0777);
	if (fds == -1)
	{
		perror("open");
		exit(1);
	}
	dup2(fds, 1);
	close(fds);
}
void	handle_redir(t_list *str, int fd[][2], int i)
{
	if (str->file != NULL)
	{
		while (str->file)
		{
			if (str->file->name != NULL)
			{
				if (str->file->type == 'H')
					handle_here_doc(str);
				else if (str->file->type == 'I')
					handle_input(str);
				else if (str->file->type == 'O')
					handle_output(str);
				else if (str->file->type == 'A')
					handle_append(str);
			}
			str->file = str->file->next;
		}
	}
}
void execute_chile(t_list *str, int fd[][2], int i, int k)
{
	char **ptr = ft_split(str->str, ' ');
	if (str->out != NULL)
	{
		int out = open(str->out, O_CREAT | O_RDWR , 0777);
		if (out == -1)
		{
        fprintf(stderr, "could not open the file : %s", str->out);			
            exit(1);
		}
		dup2(out, 1);
	}
	else
	{
		if (ft_lstsize(str) > 1)
			dup2(fd[k][1], 1);
	}
	
	if (str->in != NULL)
	{
		int in = open(str->in, O_RDWR , 0777);
		if (in == -1)
		{
        fprintf(stderr,"Bash No such file or directory: %s", str->in);
			exit(1);
		}
		dup2(in, 0);
		close(in);
	}
	else if (ft_lstsize(str) != i) 
	{
		dup2(fd[k - 1][0], 0);
		close(fd[k - 1][0]);
	}
	int temp = k;
	while (temp)
	{
		close(fd[k - temp][0]);
		close(fd[k - temp][1]);
		temp--;
	}
	int f = execve(ptr[0], ptr, NULL);	
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
			execute_chile(str, fd, i, k);
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
	str->in = NULL;
	str->out = NULL;
	str->str = "/bin/ls -la";
	str->next = NULL;
	ptr = malloc(sizeof(t_list));
	str->next = ptr;
	ptr->in = NULL;
	ptr->next = NULL;
	ptr->out = "OPLA";
	ptr->str = "/usr/bin/wc";
	ptr = malloc(sizeof(t_list));
    str->next->next = ptr;
	ptr->in = "test.c";
	ptr->next = NULL;
	ptr->out = "OPLA";
	ptr->str = "/bin/cat";
	str->next->next = ptr;
	execute(str);
}