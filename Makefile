# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: antoine <antoine@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/02 17:24:39 by anloisea          #+#    #+#              #
#    Updated: 2022/11/18 14:26:19 by antoine          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell
SRCS		= 	main.c \
				error.c \
				utils.c \
				paths.c \
				./lexer/lexer.c \
				./lexer/token.c \
				./parser/parser.c \
				./parser/tree.c \
				./parser/parsing_utils.c \
				./parser/parsing_closed_quotes.c \
				./parser/var_def.c \
				./parser/here_doc.c \
				./parser/parsing_dollar_token.c \
				pipex.c \
				processes.c \
				free.c\
				display_tmp.c\
				./builtins/echo.c \
				./builtins/env.c \
				./builtins/pwd.c \
				./builtins/cd.c \
				./builtins/export.c \
				./builtins/unset.c \
				./builtins/check_for_builtins.c\
				processes_utils.c\

				
OBJS		=	${SRCS:.c=.o}

CFLAGS		= -Wall -Wextra -Werror
CC			= 	gcc			
LIB			= 	libft/libft.a

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o} -g

all:		${LIB} ${NAME}

${LIB}:
			@make all -sC ./libft

${NAME}:	${LIB}	${OBJS}
			${CC} ${CFLAGS} ${OBJS} -L./libft -lft  -o ${NAME} -lreadline
			@echo "\033[92mminishell compiled successfully\033[0m"

clean:
			@make clean -sC ./libft
			rm -rf ${OBJS}

fclean:		clean
			@make fclean -sC ./libft
			rm -rf ${NAME} ${LIB}

re:			fclean all

.PHONY:		all clean fclean re
