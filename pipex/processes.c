/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemma <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 12:50:08 by mdemma            #+#    #+#             */
/*   Updated: 2022/10/07 12:50:12 by mdemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//Distributes all processes to their dedicated program
void	test_which_child_and_exec(pid_t *child_id, int j, int **pipefd, t_tree *treetop)
{
	if (child_id[j] == 0 && j == 0)
	{
		exec_first_child(treetop->branch, pipefd);
		//free(global.cmd_withpath1);
	}
	if (child_id[j] == 0 && j == )
	{
		exec_last_child(global.cmd->all_cmd_args, global, pipefd);
		//free(global.cmd_withpath2);
	}
	if (child_id[j] == 0 && j > 0 && j < global.cmd->nb_cmds - 1)
	{
		exec_interim_children(global, pipefd, j);
		//free(global.cmd_withpath3);
	}
}

int	*check_redir(t_tree *branch)
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
	i = 0;
	while (branch->outfiles[i] && ((fd[0] == -1 && branch->outfiles[i]->index < branch->infiles[i]->index) 
		|| (fd[0] > 0))
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
		|| (fd[0] > 0))
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
void	exec_first_child(t_tree *branch, int **pipefd)
{
	int	i;
	int	*fd;

	i = 0;
	fd = check_redir(branch);
	if (fd[0] < 0 || fd[1] < 0)
		exit(EXIT_FAILURE);
	if (fd[0] > 0)
	{
		if (dup2(fd[0], 0) == -1)
			error_cmd_not_found(all_cmd_args[0][0], global, 1, pipefd);
	}
	if (fd[1] > 0)
		dup2(fd[1], 1);
	else
		dup2(pipefd[0][1], 1);
	while (i < branch->nb_pipes + 1)
	{
		ft_putnbr_fd(close(pipefd[i][0]), 2);
		ft_putnbr_fd(close(pipefd[i][1]), 2);
		i++;
	}
	execve(branch->exec_path, branch->exec_args, branch->treetop->envp);
	//error_exec(strerror(errno), all_cmd_args[0], pipefd, global);
}

//Program for last child process: execute the last cmd
//with the last pipe's reading end as stdin
//amd the outfile_fd as stdout
void	exec_last_child(char ***all_cmd_args, t_global global, int **pipefd)
{
	int		i;
	char	**s;
	int		tmp_secu;

	tmp_secu = 0;
	s = all_cmd_args[global.cmd->nb_cmds - 1];
	i = 0;
	dup2(global.input->fd_outfile, 1);
	close(global.input->fd_infile);
	close(global.input->fd_outfile);
	dup2(pipefd[global.cmd->nb_cmds - 2][0], 0);
	i = 0;
	while (i < global.cmd->nb_cmds)
	{
		close(pipefd[i][0]);
		close(pipefd[i++][1]);
	}
	if (!s[0])
		error_empty_cmd(s[0], global, 0, pipefd);
	global.cmd_withpath2 = test_path(s[0], global.all_paths);
	if (!global.cmd_withpath2)
		error_cmd_not_found(s[0], global, 0, pipefd);
	execve(global.cmd_withpath2, s, global.env);
	if (tmp_secu == -1)
		error_exec(strerror(errno), s, pipefd, global);
}

//Program for all intermediary children processes
void	exec_interim_children(t_global global, int **pipefd, int j)
{
	int	i;

	i = 0;
	dup2(pipefd[j - 1][0], 0);
	dup2(pipefd[j][1], 1);
	while (i < global.cmd->nb_cmds - 1)
	{
		close(pipefd[i][0]);
		close(pipefd[i][1]);
		i++;
	}
	if (!global.cmd->all_cmd_args[j][0])
		error_empty_cmd(global.cmd->all_cmd_args[j][0], global,
			0, pipefd);
	global.cmd_withpath3 = test_path(global.cmd->all_cmd_args[j][0],
			global.all_paths);
	if (!global.cmd_withpath3)
		error_cmd_not_found(global.cmd->all_cmd_args[j][0], global,
			0, pipefd);
	execve(global.cmd_withpath3, global.cmd->all_cmd_args[j],
		global.env);
}

//Program for the parent process (supervises the exec of cmds by the children)
void	exec_parent(t_global global, int **pipefd)
{
	int	i;
	int	status;

	i = 0;
	while (i < global.cmd->nb_cmds)
	{
		close(pipefd[i][0]);
		close(pipefd[i][1]);
		i++;
	}
	i = 0;
	while (i < global.cmd->nb_cmds)
	{
		waitpid(global.child_id[i], &status, 0);
		i++;
	}
	close(global.input->fd_infile);
	close(global.input->fd_outfile);
	free_parsing(global);
	free_pipex(global, pipefd);
}
