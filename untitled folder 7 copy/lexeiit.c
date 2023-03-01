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
typedef struct  s_lexer_struct
{
	char	c;
	unsigned int	i;
	char *content;
}t_lexer;
typedef struct	s_token
{
	 enum{
		TOKEN_ID,
		TOKEN_EQUAls,
		TOKKEN_PIPE,
		TOKEN_DOUBLE_QUTE,
		TOKEN_APPEND,
		TOKEN_HERE_DOC,
		TOKEN_REDIRECTION_INPUT,
		TOKEN_REDIRECTION_OUTPUT,
		TOKN_SLASH,
		TOKEN_BACKSLASH,
		TOKEN_SINGLE_QOUTE
	 }type;
	 char *value;
}t_token;
 void lexer_skip_whitespace(t_lexer *lexer);
 t_token *advanced_with_token(t_lexer *lexer, t_token *token);
t_token *init_token(int type, char *value)
{

}

char  *lexer_get_current_char_as_string(t_lexer *lexer)
{

}
t_token  *lexer_collect_string(t_lexer *lexer)
{

}
t_token *lexer_get_next_token(t_lexer *lexer)
{
	while ((lexer->c  != '\0') && lexer->i < strlen(lexer->content))
	{
		if (lexer->c == ' ' || lexer->c == 10)
			lexer_skip_whitespace(lexer);
		if (lexer->c == '>')
			return (advanced_with_token(lexer, init_token(TOKEN_REDIRECTION_INPUT, lexer_get_current_char_as_string(lexer))));
	}
	
}
t_lexer *init_lexer(char *content)
{
	t_lexer *lexer;

	lexer = malloc(sizeof(t_lexer));
	lexer->content = content;
	lexer->i = 0;
	lexer->c = content[lexer->i];

	return (lexer); 
}
void lexer_advanced(t_lexer *lexer)
{
	if (lexer->c != '\0' && lexer->i < strlen(lexer->content))
	{
		lexer->i++;
		lexer->c = lexer->content[lexer->i];

	}
}
t_token *advanced_with_token(t_lexer *lexer, t_token *token)
{
	lexer_advanced(lexer);
	return (token);
}
void lexer_skip_whitespace(t_lexer *lexer)
{
	while (lexer->c == ' ' || lexer->c == 10)
	{
		lexer_advanced(lexer);
	}
}