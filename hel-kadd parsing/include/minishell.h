/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hel-kadd <hel-kadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 20:38:24 by hel-kadd          #+#    #+#             */
/*   Updated: 2023/03/09 19:11:06 by hel-kadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdlib.h>

typedef struct s_token {
    enum {
        TOKEN_APEND,
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
    } type;
	char *value;
	struct s_token *next;
} t_token;

typedef struct s_redirection {
	int type;
	char *filename;
	struct s_redirection *next;
} t_redirection;

typedef struct s_location {
    int s;
    int l;
} t_des;

//token fuction
void ft_add_back_token(t_token **list_token, t_token *new_token);
t_token *initialize_tokens(char *value, int type);
void add_token(t_token **token, int type,char *value, int len);
//str function for help parsing tokens
char	*ft_strchr(const char *s, int c);
char *ft_strndup(const char *s, size_t n);
size_t	ft_strlen(const char *str);
char	*ft_strdup(const char *src);
//mem function for help parsing tokens
void	*ft_memcpy(void *dst, const void *src, size_t n);
//utils function
int is_charset(char c);
int is_whitespace(char c);

#endif