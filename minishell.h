/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 12:56:26 by anloisea          #+#    #+#             */
/*   Updated: 2022/11/18 11:02:41 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include "libft/libft.h"
# include "lexer/lexer.h"
# include "parser/parser.h"
# include "builtins/builtins.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <signal.h>

//open
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

#include <sys/wait.h>

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
}				t_minishell;


void	error(int errnum, char *msg);

//PATHS:

char	**get_paths(char *envp[]);
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

//free:
 void	free_parser(t_parser *parser);
 void	free_exit_final(t_minishell *minishell);
 void	free_tree(t_tree *treetop);
 
 //error:
 void	error_too_many_pipes(t_minishell *minishell);
 void	error_cmd_not_found(t_minishell *minishell, t_tree *branch, int **pipefd);

 //processes:
void	exec_interim_children(t_minishell *minishell, t_tree *branch, int **pipefd, int j);
void	exec_last_child(t_minishell *minishell, t_tree *branch, int **pipefd);
void	exec_first_child(t_minishell *minishell, t_tree *branch, int **pipefd);
void	test_which_child_and_exec(t_minishell *minishell, unsigned int j, int **pipefd);
int		pipex(t_minishell *minishell);
void	exec_parent(t_minishell *minishell, int **pipefd);

//Display:
void	print_var(t_minishell *minishell);
void	display_tree(t_tree *top);
void	print_tabchar(char *s,	char **tab, int i);
void	print_tab(char *s,	t_token **tab, int i);

//Variables
t_var	*var_list_init(char **envp);

#endif