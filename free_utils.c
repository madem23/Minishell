/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elpolpa <elpolpa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 17:44:01 by antoine           #+#    #+#             */
/*   Updated: 2022/12/22 10:34:07 by elpolpa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Frees tabs. */
void	free_tab(void **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{	
		free(tab[i]);
		i++;
	}
	free(tab);
}

/* Frees all mallocs of a parsing branch.*/
void	free_branch(t_tree *branch)
{
	if (branch->exec_args)
		free_tab((void **)branch->exec_args);
	if (branch->exec_path)
		free(branch->exec_path);
	if (branch->exec_name)
		free(branch->exec_name);
	if (branch->infiles)
		free(branch->infiles);
	if (branch->outfiles)
		free(branch->outfiles);
	if (branch->outfiles_app)
		free(branch->outfiles_app);
	free(branch);
}

/* Frees all mallocs of a parsing tree/subtree. */
void	free_tree(t_tree *treetop)
{
	t_tree	*tmp;

	while (treetop)
	{
		free_branch(treetop->branch);
		tmp = treetop;
		treetop = treetop->subtree;
		free(tmp);
	}
}
