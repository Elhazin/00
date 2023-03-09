#include "minishell.h"

int ft_isspace(char c)
{
    if (c == ' ' || c == '\t')
        return 1;
    return 0;
}

int ft_is_special(char c)
{
    char a = c;
    if (strchr(" ><|;", c))
        return (1);
    return (0);
}

int ft_is_redirection(t_token *token)
{
    if (token->value[0] != '<' && token->value[0] != '>')
        return (0);
    return (1);
}

int check 