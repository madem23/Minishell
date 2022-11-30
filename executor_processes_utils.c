/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_processes_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemma <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 13:06:31 by mdemma            #+#    #+#             */
/*   Updated: 2022/11/30 13:06:33 by mdemma           ###   ########.fr       */
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

void	close_pipes(unsigned int nb_pipes, int **pipefd)
{
	unsigned int	i;

	i = 0;
	while (i < nb_pipes && pipefd)
	{
		close(pipefd[i][0]);
		close(pipefd[i][1]);
		i++;
	}
}
