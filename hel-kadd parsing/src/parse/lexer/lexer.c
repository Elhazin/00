/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouzanb <abouzanb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 19:21:09 by hel-kadd          #+#    #+#             */
/*   Updated: 2023/03/10 00:15:09 by abouzanb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

//funcrion handle pipe and semi
int lexer_semi_pipe(t_token **token, int i, char *line)
{
    if (line[i] == ';')
        add_token(token, TOKEN_SEMI, line + i, 1);
    if (line[i] == '|')
        add_token(token, TOKEN_PIPE, line + i, 1);
    return (i);
}

//function to handle redirection 
int lexer_redirection(t_token **token, int i, char *line)
{
    if (line[i] == '<')
    {
        if (line[i + 1] == '<')
            add_token(token, TOKEN_HERE_DOC, line + i++, 2);
        else
            add_token(token, TOKEN_RED_INFILE, line + i, 1);
        i++;
    }
    else
    {
        if (line[i + 1] == '>')
            add_token(token, TOKEN_APEND, line + i, 2);
        
        else 
            add_token(token, TOKEN_RED_OUTFILE, line + i, 1);
        i++;
    }
    return (i);
}

//to handle new line
void lexer_new_line(t_token **token,int i, char *line)
{
    add_token(token, TOKEN_NEW_LINE, line + i, 1);
}

//function to handele word
int lexer_is_word(t_token **token, char *line)
{
    int i;

    i = 0;
    while (!is_charset(line[i]))
        i++;
    add_token(token, TOKEN_STR, line + i, i);
    return i;
}

//function last word
void lexer_last_word(t_token **token, int i, int s, char *line)
{
    if (i >= s)
        add_token(token, TOKEN_STR, line  + s, i - s + 1);
}



//function single quote 
//create function that complite the single quote
int single_quotes(t_token **token, char *input, int i, int s)
{
    while (input[i] || input[i] != 39)
        i++;
    add_token(token, TOKEN_STR, input + s, i - s);
    i++;
    return (i);
}

// int double_quotes(t_token **token, char *input,int i, int s)
// {
    
// }

t_token *lexer(char *input)
{
    t_token *head;
    int i;
    int s;
    int double_quotes;

    double_quotes = 1;
    i = 0;
    head = NULL;
    while (is_whitespace(input[i]))
        i++;
    s = i;
    while (input[i])
    {
        if (input[i] == 39)
            s = single_quotes(&head, input, i++, s) + 1;
        if (!is_charset(input[i]))
            s = lexer_is_word(&head, input) + 1;
        else if (input[i] == '|' || input[i] == ';')
            s = lexer_semi_pipe(&head, i, input) + 1;
        if (input[i] == '\0' || input[i + 1] == '\n')
            lexer_last_word(&head, i, s, input);
        i++;
        if (input[i] == '\n' || input[i + 1] == '\0')
            lexer_new_line(&head, i, input);
    }
    return (head);
}


// void redirection_token(t_token **token, char *string, t_des *des)
// {
//     if (string[des->l] == '<')
//     {
//         if (string[des->l+1] == '<')
//         {
//             ft_add_back_token(initialize_tokens(ft_strndup(string, des->l), TOKEN_HERE_DOC), token);
//             des->l++;
//         }
//         else 
//         {
//             ft_add_back_token(initialize_tokens(ft_strndup(string, des->l), TOKEN_RED_INFILE), token);
//         }
//     }
//     else
//     {
//          ft_add_back_token(initialize_tokens(ft_strndup(string, des->l), TOKEN_RED_OUTFILE), token);
//     }
//     des->s = des->l + 1;
// }

// void semi_token(t_token **token, char *string, t_des *des)
// {
//     if (string[des->l == ';'])
//          ft_add_back_token(initialize_tokens(ft_strndup(string, des->), TOKEN_SEMI), token);
//     else
//          ft_add_back_token(initialize_tokens(ft_strndup(string, des->l), TOKEN_PIPE), token);
//     des->s = des->l + 1;
// }

// void double_quote_token(t_token **token, char *string, t_loc *des)
// {
//     if ()
// }

// void last_word_token(t_token **token, char *string, t_loc *des)
// {
//     if (des->l == des->s)
//         ft_add_back_token(initialize_tokens(ft_strndup(string, des->l), TOKEN_STR), token);
// }