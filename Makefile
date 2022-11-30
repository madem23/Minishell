# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: antoine <antoine@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/02 17:24:39 by anloisea          #+#    #+#              #
#    Updated: 2022/11/26 14:20:23 by antoine          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell
SRCS		= 	main.c \
				error.c \
				utils.c \
				paths.c \
				./lexer/lexer.c \
				./lexer/token.c \
				./lexer/lexer_extraction.c \
				./parser/parser.c \
				./parser/parser_tree.c \
				./parser/parser_utils.c \
				./parser/parser_here_doc.c \
				./expander/expander_conversion_utils.c \
				./expander/expander_tree.c \
				./expander/expander_tree_utils.c \
				./expander/expander.c \
				./builtins/echo.c \
				./builtins/env.c \
				./builtins/pwd.c \
				./builtins/cd.c \
				./builtins/export.c \
				./builtins/unset.c \
				./builtins/check_for_builtins.c\
				./builtins/ft_exit.c \
				executor_processes_utils.c\
				var_declaration.c \
				var_declaration_utils.c \
				executor.c \
				executor_processes.c \
				free.c\
				display_tmp.c\

				
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
