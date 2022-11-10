/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemma <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 12:45:20 by mdemma            #+#    #+#             */
/*   Updated: 2022/10/07 12:45:22 by mdemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <unistd.h>
# include <stdio.h>
# include <sys/wait.h>
# include <errno.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include "../minishell.h"
# include "../parser/parser.h"
# include "../libft/libft.h"

typedef struct s_cmd
{
	int		nb_cmds;
	char	***all_cmd_args;
}				t_cmd;

//here_doc -> 1 == TRUE, 0 == FALSE
typedef struct s_input
{
	char	**av;
	int		i_lastav;
	int		fd_infile;
	int		fd_outfile;
	int		heredoc;
}				t_input;

typedef struct s_global
{
	t_cmd	*cmd;
	t_input	*input;
	char	**env;
	char	**all_paths;
	pid_t	*child_id;
	char	*cmd_withpath1;
	char	*cmd_withpath2;
	char	*cmd_withpath3;
}				t_global;

//char	*test_path(char *cmd, char **all_paths);
//void	error_exec(char *str, char **cmd, int **pipefd, t_global global);
// void	free_parsing(t_global global);
// void	free_pipex(t_global global, int **pipefd);
// void	exec_parent(t_global global, int **pipefd);
// void	exec_interim_children(t_global global, int **pipefd, int j);
// void	exec_last_child(char ***all_cmd_args, t_global global, int **pipefd);
void	exec_first_child(char ***all_cmd_args, t_global global, int	**pipefd);
// void	check_for_help(char	**av);
// void	heredoc_parsing(t_input *input);
// int		manage_heredoc(char **av, t_input *input);
// void	error_too_many_pipes(t_global global);
void	test_which_child_and_exec(pid_t *child_id, t_global global,
			int j, int **pipefd);
void	error_empty_cmd(char *cmd, t_global global, int x, int **pipefd);
void	error_cmd_not_found(char *cmd, t_global global, int x, int **pipefd);
int		pipex(t_tree *top);
void	open_check_files(t_tree *top);

#endif
