/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-kadd <hel-kadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 20:38:24 by hel-kadd          #+#    #+#             */
/*   Updated: 2023/03/14 20:09:55 by hel-kadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

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

typedef struct s_token {
    enum {
        TOKEN_STR,
        TOKEN_EQUALS,
        TOKEN_LESS,
        TOKEN_GREATER,
        TOKEN_GREATGREATER,
        TOKEN_PIPE,
        TOKEN_SEMI,
        TOKEN_GP,
        TOKEN_DP,
        TOKEN_RED_INFILE,
        TOKEN_RED_OUTFILE,
        TOKEN_AND,
        TOKEN_ENV,
        TOKEN_HERE_DOC,
        TOKEN_NEW_LINE,
        TOKEN_SINGLE_QUOTE,
        TOKEN_DOUBLE_QUOTE,
        TOKEN_APEND,
        TOKEN_DOLLAR,
    } type;
	char *value;
	struct s_token *next;
} t_token;

typedef struct s_redirection {
	int type;
	char *filename;
	struct s_redirection *next;
} t_redirection;

typedef struct s_argument {
    char *args;
    struct s_argument *next;
} t_args;

typedef struct s_simple_command{
    char *cmd;
    int nbr_args;
    int nbr_red;
    t_redirection *red;
    t_args *args;
    struct s_simple_command *next;
} t_simple_command;

//token fuction
void ft_add_back_token(t_token **list_token, t_token *new_token);
t_token *initialize_tokens(char *value, int type);
void add_token(t_token **token, int type, char *value, int i, int s);
t_token *lexer(char *input);
int is_special_char(char c);
//str function for help parsing tokens
char	*ft_strchr(const char *s, int c);
char *ft_strndup(const char *s, size_t n);
size_t	ft_strlen(const char *str);
char	*ft_strdup(const char *src);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
//mem function for help parsing tokens
void	*ft_memcpy(void *dst, const void *src, size_t n);
//utils function
int is_charset(char c);
int is_whitespace(char c);

#endif