/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemma <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 13:10:21 by mdemma            #+#    #+#             */
/*   Updated: 2022/11/30 13:10:24 by mdemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

//Creates n pipes, then n child processes and executes all commands
int	executor(t_minishell *minishell)
{
	unsigned int	i;
	int				**pipefd;
	int				tmp_secu;

	i = 0;
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
