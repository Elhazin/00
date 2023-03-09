/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-kadd <hel-kadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 19:11:40 by hel-kadd          #+#    #+#             */
/*   Updated: 2023/03/09 20:07:48 by hel-kadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "/Users/hel-kadd/Desktop/minishell/include"

//init_tokens
t_token *initialize_tokens(char *value, int type)
{
    t_token *token;

    if (!value)
        return (NULL);
    token = (t_token *)malloc(sizeof(t_token));
    if (!token)
        return (NULL);
    token->type = type;
    token->value = value;
    token->next = NULL;
    return (token);
}

void add_token(t_token **token, int type, char *value, int len)
{
    ft_add_back_token(token, initialize_tokens(ft_strndup(value , len), type));
}

void ft_add_back_token(t_token **list_token, t_token *new_token)
{
    t_token *tmp;

    tmp = *list_token;
    if (!tmp)
    {
        *list_token = new_token;
        return ;
    }
    while (tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = new_token;
}

// void token_skip_whitespace()
