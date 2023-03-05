#include "minishell.h"

int main()
{
    t_exeuction *str = malloc(sizeof(t_exeuction));
    str->file  = malloc(sizeof(t_file));
	str->file->name = "main.c";
	str->file->type = 'I';
	str->file->next = NULL;
	str->str = "/bin/cat";
	t_exeuction *ptr  = malloc(sizeof(t_exeuction));
	ptr->file = NULL;
	ptr->str = "env";
	ptr->next = NULL;
	 str->next = ptr;
    execution(str);
}
