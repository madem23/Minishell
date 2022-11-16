/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 12:56:26 by anloisea          #+#    #+#             */
/*   Updated: 2022/11/16 12:34:03 by antoine          ###   ########.fr       */
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

char	**get_paths();
char	*check_exec_paths(char **paths, char *exec_called);

//Utils:

int		ft_isaccepted(char c);
int 	tab_len(char **tab);
char	*get_prompt();

//char	*test_path(char *cmd, char **all_paths);
//void	error_exec(char *str, char **cmd, int **pipefd, t_global global);
// void	free_parsing(t_global global);
// void	free_pipex(t_global global, int **pipefd);
// void	exec_parent(t_global global, int **pipefd);
void	exec_interim_children(t_tree *branch, int **pipefd, int j);
void	exec_last_child(t_tree *branch, int **pipefd);
void	exec_first_child(t_tree *branch, int **pipefd);
// void	check_for_help(char	**av);
// void	heredoc_parsing(t_input *input);
// int		manage_heredoc(char **av, t_input *input);
// void	error_too_many_pipes(t_global global);
void	test_which_child_and_exec(pid_t *child_id, unsigned int j, int **pipefd, t_tree *treetop);
//void	error_empty_cmd(char *cmd, t_global global, int x, int **pipefd);
//void	error_cmd_not_found(char *cmd, t_global global, int x, int **pipefd);
int		pipex(t_tree *top);
void	exec_parent(pid_t *child_id, t_tree *treetop, int **pipefd);

#endif