/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 12:50:08 by mdemma            #+#    #+#             */
/*   Updated: 2022/11/30 13:06:27 by mdemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>

//Distributes all processes to their dedicated program
void	test_which_child_and_exec(t_minishell *minishell, unsigned int j, int **pipefd)
{
	t_tree	*tmp;
	if (minishell->p_id[j] == 0 && j == 0)
	{
		exec_first_child(minishell, minishell->tree->branch, pipefd);
		//free(global.cmd_withpath1);
	}
	if (minishell->p_id[j] == 0 && j == minishell->tree->nb_pipes)
	{
		tmp = minishell->tree;
		while (tmp->subtree)
			tmp = tmp->subtree;
		exec_last_child(minishell, tmp->branch, pipefd);
		//free(global.cmd_withpath2);
	}
	if (minishell->p_id[j] == 0 && j > 0 && j < minishell->tree->nb_pipes)
	{
		exec_interim_children(minishell, get_branch(minishell->tree, j), pipefd, j);
		//free(global.cmd_withpath3);
	}
}

int	*check_redir_open_files(t_tree *branch)
{
	int	i;
	int	*fd;

	i = 0;
	fd = malloc(sizeof(int) * 2);
	fd[0] = 0;
	fd[1] = 0;
	while (branch->infiles[i])
	{
		fd[0] = open(branch->infiles[i]->value, O_RDONLY);
		if (fd[0] == -1)
		{
			perror(branch->infiles[i]->value);
			break;
		}
		i++;
	}
	if (fd[0] != -1 && ((i == 0 && branch->here_doc >= 0 ) || (i >= 1 && branch->here_doc >= 0 && branch->infiles[i - 1]->index < branch->here_doc))) 
	{
		if (count_tk(branch->first_token, branch->end_index, TK_DLOWER) > 1)
			fd[0] = open("tmp_empty_heredoc.txt", O_CREAT | O_RDWR | O_TRUNC, 777);
		else
			fd[0] = open("tmp_heredoc.txt", O_RDONLY);
	}
	i = 0;
	while (branch->outfiles[i] && ((fd[0] == -1 && branch->outfiles[i]->index < branch->infiles[i]->index) 
		|| (fd[0] >= 0)))
	{
		fd[1] = open(branch->outfiles[i]->value, O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (fd[1] == -1)
		{
			perror(branch->outfiles[i]->value);
			break;
		}
		i++;
	}
	i = 0;
	while (branch->outfiles_append[i] && ((fd[0] == -1 && branch->outfiles_append[i]->index < branch->infiles[i]->index) 
		|| (fd[0] >= 0)))
	{
		fd[1] = open(branch->outfiles_append[i]->value, O_CREAT | O_RDWR | O_APPEND, 0644);
		if (fd[1] == -1)
		{
			perror(branch->outfiles_append[i]->value);
			break;
		}
		i++;
	}
	return (fd);
}


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
void	exec_interim_children(t_minishell *minishell, t_tree *branch, int **pipefd, int j)
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

//Program for the parent process (supervises the exec of cmds by the children)
void	exec_parent(t_minishell *minishell, int **pipefd)
{
	unsigned int	i;

	i = 0;
	while (i < minishell->tree->nb_pipes + 1 && pipefd)
	{
		close(pipefd[i][0]);
		close(pipefd[i][1]);
		i++;
	}
	i = 0;
	while (i < minishell->tree->nb_pipes + 1)
	{
	 	minishell->sa.sa_handler = &handler_sigint_child;
	 	sigaction(SIGINT, &minishell->sa, NULL);
		waitpid(minishell->p_id[i], &exit_status, 0);
		if (WIFSIGNALED(exit_status) && WTERMSIG(exit_status) == SIGINT)
				exit_status = 130;
		else
			exit_status = WEXITSTATUS(exit_status);
		i++;
	}
	if (minishell->tree->branch->exec_name && !ft_strcmp(minishell->tree->branch->exec_name, "cd"))
		exit_status = cd(minishell->tree->branch->exec_args, minishell);
	if (minishell->tree->branch->exec_name && !ft_strcmp(minishell->tree->branch->exec_name, "export"))
		exit_status = export(minishell->tree->branch, minishell);
	if (minishell->tree->branch->exec_name && !ft_strcmp(minishell->tree->branch->exec_name, "unset"))
		exit_status = unset(minishell->tree->branch->exec_args, minishell);
	if (minishell->tree->branch->exec_name && !ft_strcmp(minishell->tree->branch->exec_name, "exit"))
	{

		ft_exit(minishell->tree->branch->exec_args);
	}
	free_end_executor(minishell, pipefd);
	free_tree(minishell->tree);
	free_parser(minishell->parser);
	minishell->sa.sa_handler = &handler_sigint_main;
	sigaction(SIGINT, &minishell->sa, NULL);
}
