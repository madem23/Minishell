/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 12:50:08 by mdemma            #+#    #+#             */
/*   Updated: 2022/11/15 16:58:37 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tree	*get_branch(t_tree *treetop, unsigned int j)
{
	t_tree			*tmp;
	unsigned int	i;

	tmp = treetop;
	i = 0;
	while (tmp->subtree && i++ < j)
		tmp = tmp->subtree;
	//dprintf(2, "Pour process : %d, BRANCHE = %s\n", j, tmp->branch->exec_name);
	return (tmp->branch);
}

//Distributes all processes to their dedicated program
void	test_which_child_and_exec(pid_t *child_id, unsigned int j, int **pipefd, t_tree *treetop)
{
	t_tree	*tmp;
	if (child_id[j] == 0 && j == 0)
	{
		exec_first_child(treetop->branch, pipefd);
		//free(global.cmd_withpath1);
	}
	if (child_id[j] == 0 && j == treetop->nb_pipes)
	{
		tmp = treetop;
		while (tmp->subtree)
			tmp = tmp->subtree;
		exec_last_child(tmp->branch, pipefd);
		//free(global.cmd_withpath2);
	}
	if (child_id[j] == 0 && j > 0 && j < treetop->nb_pipes)
	{
		exec_interim_children(get_branch(treetop, j), pipefd, j);
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
void	exec_first_child(t_tree *branch, int **pipefd)
{
	unsigned int	i;
	int	*fd;

	i = 0;
	fd = check_redir_open_files(branch);
	if (fd[0] < 0 || fd[1] < 0 || !branch->exec_name)
		exit(EXIT_FAILURE);
	if (fd[0] > 0)
		dup2(fd[0], STDIN_FILENO);
	if (fd[1] > 0)
		dup2(fd[1], STDOUT_FILENO);
	else if (branch->piped_output == true)
		dup2(pipefd[0][1], STDOUT_FILENO);
	while (i < branch->treetop->nb_pipes && pipefd)
	{
		close(pipefd[i][0]);
		close(pipefd[i][1]);
		i++;
	}
	//if (check_for_builtins(branch))
	if (!ft_strncmp(branch->exec_name, "cd", ft_strlen(branch->exec_name)))
		exit(EXIT_SUCCESS);
	if (!branch->exec_path)
	{	
		perror("Command not found");
		exit(EXIT_FAILURE);
	}
	execve(branch->exec_path, branch->exec_args, branch->treetop->envp);
}

//Program for last child process: execute the last cmd
//with the last pipe's reading end as stdin
//amd the outfile_fd as stdout"
void	exec_last_child(t_tree *branch, int **pipefd)
{
	unsigned int		i;
	char	**cmd;
	int		*fd;

	cmd = branch->exec_args;
	i = 0;
	fd = check_redir_open_files(branch);
	dprintf(2, "branch->piped_input = %d\n", branch->piped_input);
	if (fd[0] < 0 || fd[1] < 0 || !branch->exec_name)
		exit(EXIT_FAILURE);
	if (fd[0] > 0)
		dup2(fd[0], STDIN_FILENO);
	else if (branch->piped_input == true)
		dup2(pipefd[branch->treetop->nb_pipes - 1][0], STDIN_FILENO);
	if (fd[1] > 0)
		dup2(fd[1], STDOUT_FILENO);
	while (i < branch->treetop->nb_pipes)
	{
		close(pipefd[i][0]);
		close(pipefd[i++][1]);
	}
	if (check_for_builtins(branch))
		exit(EXIT_SUCCESS);
	if (!branch->exec_path)
	{	
		perror("Command not found");
		exit(EXIT_FAILURE);
	}
	//if (!global.cmd_withpath2)
		//error_cmd_not_found(s[0], global, 0, pipefd);
	execve(branch->exec_path, cmd, branch->treetop->envp);
}

//Program for all intermediary children processes
void	exec_interim_children(t_tree *branch, int **pipefd, int j)
{
	unsigned int	i;
	int	*fd;

	i = 0;
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
	while (i < branch->treetop->nb_pipes)
	{
		close(pipefd[i][0]);
		close(pipefd[i][1]);
		i++;
	}
	if (check_for_builtins(branch))
	{
		puts(branch->exec_name);
		exit(EXIT_SUCCESS);
	}
	if (!branch->exec_path)
	{	
		perror("Command not found");
		exit(EXIT_FAILURE);
	}
	execve(branch->exec_path, branch->exec_args, branch->treetop->envp);
}

//Program for the parent process (supervises the exec of cmds by the children)
void	exec_parent(pid_t *child_id, t_tree *treetop, int **pipefd)
{
	unsigned int	i;
	int	status;

	i = 0;
	if (!ft_strncmp(treetop->branch->exec_name, "cd", ft_strlen(treetop->branch->exec_name)))
	{	
		printf("COUCOU\n");
		cd(treetop->branch->exec_args);
	}
	while (i < treetop->nb_pipes + 1 && pipefd)
	{
		close(pipefd[i][0]);
		close(pipefd[i][1]);
		i++;
	}
	i = 0;
	while (i < treetop->nb_pipes + 1)
	{
		waitpid(child_id[i], &status, 0);
		i++;
	}
	//close(input->fd_infile);
	///close(input->fd_outfile);
	//free_parsing(global);
	//free_pipex(global, pipefd);
}
