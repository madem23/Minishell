/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 13:10:21 by mdemma            #+#    #+#             */
/*   Updated: 2022/12/08 18:11:53 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Distributes all child processes to their dedicated program
void	test_which_child_and_exec(t_minishell *minishell, unsigned int j,
	int **pipefd)
{
	t_tree	*tmp;

	printf("----DEBUT pour j = %d, pid = %d, getpid= %d\n", j, minishell->p_id[j], getpid());
	if (minishell->p_id[j] == 0 && j == 0)
	{
		printf("----dans loop first, pour j = %d, pid = %d, getpid= %d\n", j, minishell->p_id[j], getpid());
		exec_first_child(minishell, minishell->tree->branch, pipefd);
	}
	if (minishell->p_id[j] == 0 && j == minishell->tree->nb_pipes)
	{
		printf("----dans loop last, pour j = %d, pid = %d, getpid= %d\n", j, minishell->p_id[j], getpid());
		tmp = minishell->tree;
		while (tmp->subtree)
			tmp = tmp->subtree;
		exec_last_child(minishell, tmp->branch, pipefd);
	}
	if (minishell->p_id[j] == 0 && j > 0 && j < minishell->tree->nb_pipes)
		exec_interim_children(minishell, get_branch(minishell->tree, j),
			pipefd, j);
}

/* First sas to send each process to the right function. */
void	exec_processes(t_minishell *minishell, int **pipefd)
{
	unsigned int	i;

	i = 0;
	while (i <= minishell->tree->nb_pipes)
	{
		test_which_child_and_exec(minishell, i, pipefd);
		i++;
	}
	if (minishell->p_id[0] > 0)
		exec_parent(minishell, pipefd);
}

//Calls fork (and thus create a child process) for each command
//Returns a tab of int for containing the process IDs of all children
pid_t	*create_all_children(t_tree *treetop)
{
	pid_t	*child_id;
	int		j;
	int		nb;

	j = 0;
	child_id = malloc(sizeof(child_id) * (treetop->nb_pipes + 1));
	if (!child_id)
		exit(EXIT_FAILURE);
	child_id[j] = fork();
	nb = treetop->nb_pipes;
	while (nb > 0)
	{
		if (child_id[j] != 0)
			child_id[++j] = fork();
		nb--;
	}
	return (child_id);
}

int	check_for_heredoc_error(void)
{
	if (g_global.sigint_heredoc == true)
	{
		g_global.sigint_heredoc = false;
		return (1);
	}
	return (0);
}

//Creates n pipes, then n child processes and executes all commands
int	executor(t_minishell *minishell)
{
	unsigned int	i;
	int				**pipefd;
	int				tmp_secu;

	i = 0;
	if (check_for_heredoc_error())
		return (1);
	if (minishell->tree->nb_pipes > 0)
	{
		pipefd = malloc(sizeof(pipefd) * (minishell->tree->nb_pipes + 1));
		while (i < minishell->tree->nb_pipes + 1)
		{
			pipefd[i] = malloc(sizeof(int) * 2);
			tmp_secu = pipe(pipefd[i]);
			if (tmp_secu == -1)
				error_too_many_pipes(minishell);
			i++;
		}
		minishell->pipefd = pipefd;
	}
	else
		pipefd = NULL;
	minishell->p_id = create_all_children(minishell->tree);
	exec_processes(minishell, pipefd);
	return (0);
}
