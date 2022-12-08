/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_processes_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 13:06:31 by mdemma            #+#    #+#             */
/*   Updated: 2022/12/08 17:48:47 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Returns the requested branch number 'j' of the g_global tree.
t_tree	*get_branch(t_tree *treetop, unsigned int j)
{
	t_tree			*tmp;
	unsigned int	i;

	tmp = treetop;
	i = 0;
	while (tmp->subtree && i++ < j)
		tmp = tmp->subtree;
	return (tmp->branch);
}

//Closes all pipes.
void	close_pipes(unsigned int nb_pipes, int **pipefd)
{
	unsigned int	i;

	i = 0;
	while (pipefd && i < nb_pipes + 1)
	{
		close(pipefd[i][0]);
		close(pipefd[i][1]);
		i++;
	}
}
