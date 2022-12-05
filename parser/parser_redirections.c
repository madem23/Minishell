/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemma <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 17:52:25 by mdemma            #+#    #+#             */
/*   Updated: 2022/12/05 17:52:31 by mdemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "../minishell.h"
#include "../libft/libft.h"

t_token	**filling_redir_files_tab(t_tree *branch, int size, unsigned int type)
{
	t_token	*tmp;
	t_token	**tab;
	int		i;

	i = 0;
	tmp = branch->first_token;
	tab = malloc(sizeof(t_token *) * size);
	if (!tab)
	{
		printf("Error in allocating redir tab.\n");
		exit(EXIT_FAILURE);
	}
	while (tmp && tmp->index <= branch->end_index)
	{
		if (tmp->e_tk_type == type)
		{
			tmp->parsed = true;
			tmp = tmp->next_token;
			tmp->parsed = true;
			tab[i++] = tmp;
		}
		tmp = tmp->next_token;
	}
	tab[i] = NULL;
	return (tab);
}

void	parsing_redir(t_tree *branch)
{
	t_token	*tmp;

	tmp = branch->first_token;
	branch->nb_infiles = 0;
	branch->nb_outfiles = 0;
	branch->nb_outfiles_append = 0;
	while (tmp && tmp->index <= branch->end_index)
	{
		if (tmp->e_tk_type == TK_LOWER)
			branch->nb_infiles++;
		else if (tmp->e_tk_type == TK_GREATER)
			branch->nb_outfiles++;
		else if (tmp->e_tk_type == TK_DGREATER)
			branch->nb_outfiles_append++;
		tmp = tmp->next_token;
	}
	branch->infiles = filling_redir_files_tab(branch,
			branch->nb_infiles + 1, TK_LOWER);
	branch->outfiles = filling_redir_files_tab(branch,
			branch->nb_outfiles + 1, TK_GREATER);
	branch->outfiles_append = filling_redir_files_tab(branch,
			branch->nb_outfiles_append + 1, TK_DGREATER);
}
