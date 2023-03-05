#include "minishell.h"

int main(int ac, char **av, char **env)
{
	fill_env(env);
    t_exeuction *str = malloc(sizeof(t_exeuction));
    str->file  = malloc(sizeof(t_file));
	 str->file->name = "file.txt";
	 str->file->type = 'O';
	 str->file->next = NULL;
	str->str = "/bin/ls";
	t_exeuction *ptr  = malloc(sizeof(t_exeuction));
	ptr->file = NULL;
	ptr->str = "/bin/cat";
	ptr->next = NULL;
	  str->next = ptr;
    execution(str);

}
 