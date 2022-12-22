/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elpolpa <elpolpa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 17:52:25 by mdemma            #+#    #+#             */
/*   Updated: 2022/12/22 10:37:39 by elpolpa          ###   ########.fr       */
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
	check_malloc((void *)tab);
	while (tmp && tmp->index <= branch->end_index)
	{
		if (tmp->e_tk_type == type)
		{
			tmp->parsed = true;
			tmp = tmp->next_token;
			// if (tmp->e_tk_type == TK_LOWER || tmp->e_tk_type == TK_GREATER
			// 	|| tmp->e_tk_type == TK_DGREATER || tmp->e_tk_type == TK_PIPE
			// 	|| tmp->e_tk_type == TK_EOC)
			// 	error_syntax(tmp->value);
			tmp->parsed = true;
			tab[i++] = tmp;
		}
		tmp = tmp->next_token;
	}
	tab[i] = NULL;
	return (tab);
}

int	check_error_redir(t_tree *branch)
{
	t_token	*tmp;
	
	tmp = branch->first_token;
	while (tmp && tmp->index <= branch->end_index)
	{
		if (tmp->e_tk_type == TK_LOWER || tmp->e_tk_type == TK_GREATER
			|| tmp->e_tk_type == TK_DGREATER || tmp->e_tk_type == TK_DLOWER)
		{
			tmp = tmp->next_token;
			if (tmp->e_tk_type == TK_LOWER || tmp->e_tk_type == TK_GREATER
				|| tmp->e_tk_type == TK_DGREATER || tmp->e_tk_type == TK_PIPE
				|| tmp->e_tk_type == TK_DLOWER || tmp->e_tk_type == TK_EOC)
			{
				error_syntax(tmp->value);
				return (tmp->index - 1);
			}
		}
		tmp = tmp->next_token;
	}
	return (-2);
}

int	parsing_redir(t_tree *branch)
{
	t_token	*tmp;
	int		n;

	tmp = branch->first_token;
	branch->nb_infiles = 0;
	branch->nb_outfiles = 0;
	branch->nb_outfiles_app = 0;
	while (tmp && tmp->index <= branch->end_index)
	{
		if (tmp->e_tk_type == TK_LOWER)
			branch->nb_infiles++;
		else if (tmp->e_tk_type == TK_GREATER)
			branch->nb_outfiles++;
		else if (tmp->e_tk_type == TK_DGREATER)
			branch->nb_outfiles_app++;
		tmp = tmp->next_token;
	}
	n = check_error_redir(branch);
	if (n > -2)
		return (n);
	branch->infiles = filling_redir_files_tab(branch,
			branch->nb_infiles + 1, TK_LOWER);
	branch->outfiles = filling_redir_files_tab(branch,
			branch->nb_outfiles + 1, TK_GREATER);
	branch->outfiles_app = filling_redir_files_tab(branch,
			branch->nb_outfiles_app + 1, TK_DGREATER);
	return (-2);
}
