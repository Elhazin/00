/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-kadd <hel-kadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 19:21:09 by hel-kadd          #+#    #+#             */
/*   Updated: 2023/03/14 22:11:49 by hel-kadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"


// int lexer_handle_single_quotes(t_token **token, char *input, int i)
// {
//     char *var;

//     var = input + i;
//     while (input[i] && input[i] != 39)
//     {
//         var = ft_strjoin(var, &input[i]);
//         i++;
//     }
//     add_token(token, TOKEN_SINGLE_QUOTE, var, ft_strlen(var));
//     return (i);
// }

// int lexer_handle_double_quotes(t_token **token, char *input, int i, int s)
// {
//     s = i;
//     while (input[i] && input[i] != 34)
//         i++;
//     add_token(token, TOKEN_DOUBLE_QUOTE, input, i - s);
//     return (i);
// }

//funcrion handle pipe and semi
int lexer_semi_pipe(t_token **token, int i, char *input)
{
    printf("inside pipe function i = %d\n", i);
    if (input[i] == ';')
        ft_add_back_token(token, initialize_tokens(ft_strndup(input + i, 1), TOKEN_SEMI));
    if (input[i] == '|')
         ft_add_back_token(token, initialize_tokens(ft_strndup(input + i, 1), TOKEN_PIPE));
    return (i);
}

//function to handle redirection 
int lexer_redirection(t_token **token, int i, char *line)
{
    if (line[i] == '<')
    {
        if (line[i + 1] == '<')
        { 
             ft_add_back_token(token, initialize_tokens(ft_strndup(line + i, 2), TOKEN_HERE_DOC));
            i++;
        }
        else
            ft_add_back_token(token, initialize_tokens(ft_strndup(line + i, 1), TOKEN_RED_INFILE));
    }
    else
    {
        if (line[i + 1] == '>')
        {
            ft_add_back_token(token, initialize_tokens(ft_strndup(line + i, 2), TOKEN_APEND));
             i++;
        }
        else 
             ft_add_back_token(token, initialize_tokens(ft_strndup(line + i, 1), TOKEN_RED_OUTFILE));
    }
    return (i);
}

//to handle new line
// void lexer_new_line(t_token **token,int i, char *line)
// {
//     add_token(token, TOKEN_NEW_LINE, line + i, 1);
// }

// //function to handele word
int lexer_is_word(t_token **token, char *input, int i, int s)
{
    s = i;
    while (input[i] && (is_special_char(input[i]) != 0))
        i++;
    // printf("i = %d\n", i);
    add_token(token, TOKEN_STR, input, i - s, s);
    return (i);
}

//function last word
// void lexer_last_word(t_token **token, int i, int s, char *line)
// {
//     if (i >= s)
//         add_token(token, TOKEN_STR, line  + s, i - s + 1);
// }

//function single quote 
//create function that complite the single quote
// int single_quotes(t_token **token, char *input, int i, int s)
// {
//     while (input[i] != '\0' && input[i] != 39)
//         i++;
//     if (input[i] == 39)
//         i++;
//     printf("input[i] %c\n", input[i]);
//     add_token(token, TOKEN_STR, input + s, i - s);
//     i++;
//     return (i);
// }

// int lexer_token_word(t_token **token, char *input, int i, int s)
// {
//     while (is_special_char(input[i]) != 1 && input[i] != ' ')
//         i++;
//     add_token(token, TOKEN_STR,input + s, i - s);
//     return (i);
// }
// int  db_quote(t_token ** to)
t_token *lexer(char *input)
{
    t_token *head;
    int i;
    int s;
    int sq;
    int dq;

    i = 0;
    sq = 0;
    dq = 0;
    head = NULL;
    // while (is_whitespace(input[i]))
    s = i;
    // printf("input %d\n", s);
    while (input[i])
    {
        if (is_charset(input[i]) != 0  /*|| (input[i] != ' ' && input[i] != '|' && input[i] != ';')*/)
        {
            i = lexer_is_word(&head, input, i, s);
            s = i;
        }
        // if (input[i] == 39)
        //     sq++;
        // if (input[i] == 39 && sq == 1)
        // {
        //     s = lexer_handle_single_quotes(&head, input, i) + 1;
        //     i = s;
        // }
        // if (input[i] == 34)
        //     dq++;
        // if (input[i] == 34 && dq == 1)
        // {
        //     s = lexer_handle_double_quotes(&head, input, i);
        //     i = s + 1;
        // }
        if ((input[i] == '|' || input[i] == ';'))
        {
            printf("semi\n");
            i = lexer_semi_pipe(&head, i, input);
            s = i;
        }
            
        if ((input[i] == '<' || input[i] == '>'))
        {
            s = lexer_redirection(&head, i, input);
            i = s;
        }
        // // else if (input[i + 1] == '\0' || input[i + 1] == '\n')
        // //     lexer_last_word(&head, i, s, input);
        i++;
    }
    return (head);
}


