# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hel-kadd <hel-kadd@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/09 18:51:46 by hel-kadd          #+#    #+#              #
#    Updated: 2023/03/09 20:01:48 by hel-kadd         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = @cc

CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g3

# AR = @ar 

# ARFLAGS = rc

SRCS =	./src/parse/lexer/lexer.c \
		./src/parse/lexer/lexer_utils.c \
		./src/parse/utils/ft_utils.c \
		./src/parse/utils/ft_str_func.c \
		main.c 

C_RED = \033[1;31m
C_GREEN = \033[1;32m
C_L_BLUE = \033[1;34m
C_RES = \033[0m

OBJS = $(SRCS:.c=.o)

OBJSBS = $(BONUS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
		$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
		@echo "$(C_GREEN)[minishell CREATED]$(C_RES)"

clean: 
		@rm -rf $(OBJS) $(OBJSBS)
		@echo "$(C_RED)[OBJECTS REMOVED]$(C_RES)"

fclean: clean
		@rm -rf $(NAME)
		@echo "$(C_RED)[pipex REMOVED]$(C_RES)"

re : fclean all



