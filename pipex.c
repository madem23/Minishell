/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 12:54:11 by mdemma            #+#    #+#             */
/*   Updated: 2022/11/15 14:03:07 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Calls fork (and thus create a child process) for each input command
//Returns a tab of int for containing the process IDs
pid_t	*create_all_children(t_tree *treetop)
{
	pid_t	*child_id;
//	int		i;
	int		j;
	int		nb;

	j = 0;
	child_id = malloc(sizeof(child_id) * (treetop->nb_pipes + 2)); //enfants +1 parent
	if (!child_id)
		exit(EXIT_FAILURE);
	child_id[j] = fork();
	//printf("fork 1 fait, process = %d\n", child_id[j]);
	//i = 1;
	nb = treetop->nb_pipes;
	while (nb > 0)
	{
		if (child_id[j] != 0)
		{
			child_id[++j] = fork();
		//	printf("fork 2 fait, process = %d\n", child_id[j]);
		}
		nb--;
	}
	return (child_id);
}
/*
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
}*/

//Creates n pipes, then n child processes and executes all commands
int	pipex(t_tree *treetop)
{
	unsigned int		i;
	unsigned int		j;
	int		**pipefd;
//	int		tmp_secu;
	pid_t	*child_id;

	i = 0;
	if (treetop->nb_pipes > 0)
	{
		pipefd = malloc(sizeof(pipefd) * (treetop->nb_pipes + 1));
		while (i < treetop->nb_pipes + 1)
		{
			pipefd[i] = malloc(sizeof(int) * 2);
			pipe(pipefd[i]);
			//if (tmp_secu == -1)
			//	error_too_many_pipes(global);
			i++;
		}
	}
	else
		pipefd = NULL;
	child_id = create_all_children(treetop);
	j = 0;
	while (j <= treetop->nb_pipes)
	{
		test_which_child_and_exec(child_id, j, pipefd, treetop);
		j++;
	}
	if (child_id[0] > 0)
		exec_parent(child_id, treetop, pipefd);
	return (0);
}
