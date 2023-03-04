#include "minishell.h"

int main()
{
    t_exeuction *str = malloc(sizeof(t_exeuction));
    str->file  = malloc(sizeof(t_file));
	str->file->name = "d.c";
	str->file->type = 'I';
	str->file->next = NULL;
	str->str = "/bin/cat";
    execution(str);
}
