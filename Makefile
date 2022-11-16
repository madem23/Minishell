# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: antoine <antoine@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/02 17:24:39 by anloisea          #+#    #+#              #
#    Updated: 2022/11/16 11:20:43 by antoine          ###   ########.fr        #
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
				./parser/parsing_utils2.c \
				./parser/var_def.c \
				./parser/here_doc.c \
				pipex.c \
				processes.c \
				./builtins/echo.c \
				./builtins/env.c \
				./builtins/pwd.c \
				./builtins/cd.c \
				./builtins/check_for_builtins.c

		
			
				
OBJS		=	${SRCS:.c=.o}

CFLAGS		= -Wall -Wextra -Werror
CC			= 	gcc			
LIB			= 	libft/libft.a

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

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
