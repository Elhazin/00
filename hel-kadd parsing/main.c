  #include "include/minishell.h"

 int main(void)
 {
	char *str;
	while(1)//while 1 atb9a testi testi ta t3ia
	{
		str = readline("minishell : ");//this function is like get_next_line kat9ra mn stdin 
		t_token *token;
		token = NULL;
		token = lexer(str);
		while (token != NULL)
		{
			printf("value : %s\n", token->value);
			printf("type : %u\n", token->type);
			token = token->next;
		}
	}
 }

