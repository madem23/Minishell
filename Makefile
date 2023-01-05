# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anloisea <anloisea@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/02 17:24:39 by anloisea          #+#    #+#              #
#    Updated: 2023/01/05 14:55:28 by anloisea         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell
SRCS		= 	main.c \
				error.c \
				utils.c \
				paths.c \
				./lexer/lexer.c \
				./lexer/lexer_utils.c \
				./lexer/token.c \
				./lexer/lexer_extraction.c \
				./parser/parser.c \
				./parser/parser_tree.c \
				./parser/parser_redirections.c \
				./parser/parser_cmd.c \
				./parser/parser_here_doc.c \
				./parser/parser_error.c \
				./expander/expander_conversion_utils.c \
				./expander/expander_tree.c \
				./expander/expander_tree_utils.c \
				./expander/expander.c \
				./expander/expander_init_branch.c\
				./expander/expander_create_branch.c \
				./builtins/echo.c \
				./builtins/env.c \
				./builtins/pwd.c \
				./builtins/cd.c \
				./builtins/export.c \
				./builtins/unset.c \
				./builtins/check_for_builtins.c\
				./builtins/ft_exit.c \
				var_declaration.c \
				variable_utils.c \
				executor.c \
				executor_processes.c \
				executor_processes_utils.c\
				executor_redirections.c\
				free.c\
				free_utils.c\
				display_tmp.c\
				envp.c\
				is_functions.c \
				signals.c \
				check_pipe.c

				
OBJS		=	${SRCS:.c=.o}

CFLAGS		= -Wall -Wextra -Werror -I/Users/$(USER)/.brew/Cellar/readline/8.2.1/include
IFLAGS		= -L/Users/$(USER)/.brew/Cellar/readline/8.2.1/lib -lreadline
CC			= 	gcc			
LIB			= 	libft/libft.a

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o} -g 

all:		${LIB} ${NAME}

${LIB}:
			@make all -sC ./libft

${NAME}:	${LIB}	${OBJS}
			${CC} ${CFLAGS} ${OBJS} -L./libft -lft -o ${NAME} ${IFLAGS}
			@echo "\033[92mminishell compiled successfully\033[0m"

clean:
			@make clean -sC ./libft
			rm -rf ${OBJS}

fclean:		clean
			@make fclean -sC ./libft
			rm -rf ${NAME} ${LIB}

re:			fclean all

.PHONY:		all clean fclean re
