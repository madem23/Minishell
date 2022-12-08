/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_processes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 12:50:08 by mdemma            #+#    #+#             */
/*   Updated: 2022/12/08 18:06:25 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>

//Program for first child process: execute the first cmd with infile_fd as stdin
//and the first pipe's writing end as stdout
void	exec_first_child(t_minishell *minishell, t_tree *branch, int **pipefd)
{
	int	*fd;
	int	n;

	fd = check_redir_open_files(branch);
	if (fd[0] < 0 || fd[1] < 0 || !branch->exec_name)
		exit(EXIT_FAILURE);
	if (fd[0] > 0)
		dup2(fd[0], STDIN_FILENO);
	if (fd[1] > 0)
		dup2(fd[1], STDOUT_FILENO);
	else if (branch->piped_output == true)
		dup2(pipefd[0][1], STDOUT_FILENO);
	free(fd);
	close_pipes(branch->treetop->nb_pipes, pipefd);
	n = check_for_builtins(branch, minishell);
	if (n != -1)
		exit(n);
	if (!branch->exec_path && !branch->treetop->paths)
		error_cmd_path(minishell, branch, pipefd);
	if (!branch->exec_path)
		error_cmd_not_found(minishell, branch, pipefd);
	execve(branch->exec_path, branch->exec_args, minishell->envp);
}

//Program for last child process: execute the last cmd
//with the last pipe's reading end as stdin
//amd the outfile_fd as stdout"
void	exec_last_child(t_minishell *minishell, t_tree *branch, int **pipefd)
{
	char	**cmd;
	int		*fd;
	int		n;

	cmd = branch->exec_args;
	fd = check_redir_open_files(branch);
	if (fd[0] < 0 || fd[1] < 0 || !branch->exec_name)
		exit(EXIT_FAILURE);
	if (fd[0] > 0)
		dup2(fd[0], STDIN_FILENO);
	else if (branch->piped_input == true)
		dup2(pipefd[branch->treetop->nb_pipes - 1][0], STDIN_FILENO);
	if (fd[1] > 0)
		dup2(fd[1], STDOUT_FILENO);
	free(fd);
	close_pipes(branch->treetop->nb_pipes, pipefd);
	n = check_for_builtins(branch, minishell);
	if (n != -1)
		exit(n);
	if (!branch->exec_path && !branch->treetop->paths)
		error_cmd_path(minishell, branch, pipefd);
	if (!branch->exec_path)
		error_cmd_not_found(minishell, branch, pipefd);
	execve(branch->exec_path, cmd, minishell->envp);
}

//Program for all intermediary children processes
void	exec_interim_children(t_minishell *minishell, t_tree *branch,
	int **pipefd, int j)
{
	int	*fd;
	int	n;

	fd = check_redir_open_files(branch);
	if (fd[0] < 0 || fd[1] < 0 || !branch->exec_name)
		exit(EXIT_FAILURE);
	if (fd[0] > 0)
		dup2(fd[0], STDIN_FILENO);
	else if (branch->piped_input == true)
		dup2(pipefd[j - 1][0], STDIN_FILENO);
	if (fd[1] > 0)
		dup2(fd[1], STDOUT_FILENO);
	else if (branch->piped_output == true)
		dup2(pipefd[j][1], STDOUT_FILENO);
	free(fd);
	close_pipes(branch->treetop->nb_pipes, pipefd);
	n = check_for_builtins(branch, minishell);
	if (n != -1)
		exit(n);
	if (!branch->exec_path && !branch->treetop->paths)
		error_cmd_path(minishell, branch, pipefd);
	if (!branch->exec_path)
		error_cmd_not_found(minishell, branch, pipefd);
	execve(branch->exec_path, branch->exec_args, minishell->envp);
}

void	exec_parent_builtins(t_minishell *minishell)
{
	if (minishell->tree->branch->exec_name
		&& !ft_strcmp(minishell->tree->branch->exec_name, "cd"))
		g_global.exit_status = cd(minishell->tree->branch->exec_args,
				minishell);
	if (minishell->tree->branch->exec_name
		&& !ft_strcmp(minishell->tree->branch->exec_name, "export"))
		g_global.exit_status = export(minishell->tree->branch, minishell);
	if (minishell->tree->branch->exec_name
		&& !ft_strcmp(minishell->tree->branch->exec_name, "unset"))
		g_global.exit_status = unset(minishell->tree->branch->exec_args,
				minishell);
	if (minishell->tree->branch->exec_name
		&& !ft_strcmp(minishell->tree->branch->exec_name, "exit"))
	{
		ft_exit(minishell->tree->branch->exec_args);
	}
}

//Program for the parent process (supervises the exec of cmds by the children)
void	exec_parent(t_minishell *minishell, int **pipefd)
{
	unsigned int	i;

	i = 0;
	close_pipes(minishell->tree->nb_pipes, pipefd);
	while (i < minishell->tree->nb_pipes + 1)
	{
		minishell->sa.sa_handler = &handler_sigint_child;
		sigaction(SIGINT, &minishell->sa, NULL);
		waitpid(minishell->p_id[i], &g_global.exit_status, 0);
		if (WIFSIGNALED(g_global.exit_status)
			&& WTERMSIG(g_global.exit_status) == SIGINT)
			g_global.exit_status = 130;
		else
		{
			if (WIFSIGNALED(g_global.exit_status))
				g_global.exit_status = WEXITSTATUS(g_global.exit_status);
		}
		i++;
	}
	exec_parent_builtins(minishell);
	free_end_executor(minishell, pipefd);
	free_tree(minishell->tree);
	free_parser(minishell->parser);
	minishell->sa.sa_handler = &handler_sigint_main;
	sigaction(SIGINT, &minishell->sa, NULL);
}
