/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 12:56:26 by anloisea          #+#    #+#             */
/*   Updated: 2022/12/02 14:41:00 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include "libft/libft.h"
# include "lexer/lexer.h"
# include "parser/parser.h"
# include "expander/expander.h"
# include "builtins/builtins.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <signal.h>
# include <unistd.h>
# include <termios.h> 

//open
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

#include <sys/wait.h>

int	exit_status;


typedef struct s_global
{
	struct s_expander_tree	subtree;
}						t_global;

t_global	global;

typedef struct s_minishell
{
	t_var		*var_def;
	pid_t		*p_id;
	char		**envp;
	char		*current_dir;
	char		*prompt;
	char		*cmd_line;
	t_lexer		*lexer;
	t_parser	*parser;
	t_tree		*tree;
	int			**pipefd;
	struct sigaction	sa;
	struct termios old_termios;
	struct termios new_termios;
}				t_minishell;


void	error(int errnum, char *msg);

//PATHS:

char	**get_paths(t_var * var_list);
char	*check_exec_paths(char **paths, char *exec_called);

//Utils:

int		ft_isaccepted(char c);
int		ft_isaccepted_var_name(char c);
char	*get_prompt();
char	**t_strcpy(char **t_str);
char	**add_str_to_tab(char **tab, const char *str);
int		locate_char(char *s, char c);
void	close_pipes(unsigned int nb_pipes, int **pipefd);
t_tree	*get_branch(t_tree *treetop, unsigned int j);
int		ft_strchrset(const char *s, char *charset);
char	*malloc_string(int size);

//free:
 void	free_parser(t_parser *parser);
 void	free_exit_final(t_minishell *minishell);
 void	free_tree(t_tree *treetop);
void	free_tab(void **tab);
void	free_end_executor(t_minishell *minishell, int **pipefd);
void	free_tokens(t_parser *parser);

 
 //error:
 void	error_too_many_pipes(t_minishell *minishell);
 void	error_cmd_path(t_minishell *minishell, t_tree *branch, int **pipefd);
 void	error_cmd_not_found(t_minishell *minishell, t_tree *branch, int **pipefd);

 //processes:
void	exec_interim_children(t_minishell *minishell, t_tree *branch, int **pipefd, int j);
void	exec_last_child(t_minishell *minishell, t_tree *branch, int **pipefd);
void	exec_first_child(t_minishell *minishell, t_tree *branch, int **pipefd);
void	test_which_child_and_exec(t_minishell *minishell, unsigned int j, int **pipefd);
int		executor(t_minishell *minishell);
void	exec_parent(t_minishell *minishell, int **pipefd);

//Display:
void	print_var(t_minishell *minishell);
void	display_tree(t_tree *top);
void	print_tabchar(char *s,	char **tab, int i);
void	print_tab(char *s,	t_token **tab, int i);

//Variables
t_var	*var_list_init(char **envp);
int		change_var_value(t_var *list, char *name, char *value);
void	update_envp(t_minishell *minishell);
char	*get_var_value(t_var *var_list, char *name);

//signals
void	handler_sigint_child(int sig);
void	handler_sigint_main(int sig);

#endif