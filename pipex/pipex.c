/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemma <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 12:54:11 by mdemma            #+#    #+#             */
/*   Updated: 2022/10/07 12:54:14 by mdemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

//Calls fork (and thus create a child process) for each input command
//Returns a tab of int for containing the process IDs
pid_t	*create_all_children(char ***all_cmd_args, t_global global)
{
	pid_t	*child_id;
	int		i;
	int		j;
	int		nb;

	j = 0;
	child_id = malloc(sizeof(child_id) * (top->nb_pipes + 2)); //enfants +1 parent
	if (!child_id)
		exit(EXIT_FAILURE);
	child_id[j] = fork();
	i = 1;
	nb = top->nb_pipes + 1;
	while (nb > 0)
	{
		if (child_id[j] != 0)
			child_id[++j] = fork();
		nb--;
	}
	return (child_id);
}

//Opens the infile and the outfile and check for errors
void	open_check_files(t_tree *top)
{
	if (global.input->heredoc == 0)
		global.input->fd_infile = open(av[1], O_RDONLY);
	else
		global.input->fd_infile = open("tmp_heredoc.txt", O_RDONLY);
	if (global.input->fd_infile == -1)
	{
		if (global.input->heredoc == 0)
			perror(av[1]);
		else
			perror("tmp_heredoc.txt");
	}
	if (global.input->heredoc == 0)
		global.input->fd_outfile = open(av[global.input->i_lastav],
				O_CREAT | O_RDWR | O_TRUNC, 0644);
	else
		global.input->fd_outfile = open(av[global.input->i_lastav],
				O_CREAT | O_RDWR | O_APPEND, 0644);
	if (global.input->fd_outfile == -1)
	{
		perror(av[global.input->i_lastav]);
		free_parsing(global);
		exit(EXIT_FAILURE);
	}
}

//Creates n pipes, then n child processes and executes all commands
int	pipex(t_tree *toptree)
{
	int		i;
	int		j;
	int		**pipefd;
	int		tmp_secu;
	pid_t	*child_id;

	i = 0;
	//open_check_files(top);
	pipefd = malloc(sizeof(pipefd) * (toptree->nb_pipes + 1));
	while (i < top->nb_pipes + 1)
	{
		pipefd[i] = malloc(sizeof(int) * 2);
		tmp_secu = pipe(pipefd[i]);
		if (tmp_secu == -1)
			error_too_many_pipes(global);
		i++;
	}
	child_id = create_all_children(toptree);
	j = 0;
	while (j <= toptree->nb_pipes)
		test_which_child_and_exec(child_id, j++, pipefd, toptree);
	if (global.child_id[0] > 0)
		exec_parent(global, pipefd);
	return (0);
}

// int	check_env(char **env)
// {
// 	int	i;

// 	i = 0;
// 	while (env[i] && (env[i][0] != 'P' || env[i][1] != 'A'
// 			|| env[i][2] != 'T' || env[i][3] != 'H'))
// 		i++;
// 	if (env[i] && env[i][0] == 'P' && env[i][1] == 'A'
// 			&& env[i][2] == 'T' && env[i][3] == 'H')
// 		return (1);
// 	else
// 		return (0);
// }
