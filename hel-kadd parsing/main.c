#include "include/minishell.h"

int main(void)
{
	t_token *token;
	
	token = NULL;
	token = lexer(">>;|kade");
	while (token != NULL)
	{
		printf("value : %s\n", token->value);
		printf("type : %u\n", token->type);
		token = token->next;
	}
	
	// printf("type %d\n", token->type);
}