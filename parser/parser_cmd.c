/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdemma <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 17:52:03 by mdemma            #+#    #+#             */
/*   Updated: 2022/12/05 17:52:05 by mdemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "../minishell.h"
#include "../libft/libft.h"

int	count_unparsed_word(t_tree *branch)
{
	t_token	*tmp;
	int		count;

	count = 0;
	tmp = branch->first_token;
	while (tmp && tmp->index <= branch->end_index)
	{
		if ((tmp->e_tk_type == TK_WORD || tmp->e_tk_type == TK_DOLLAR
				|| tmp->e_tk_type == TK_EQUAL || tmp->e_tk_type == TK_QUOTE)
			&& tmp->parsed == false)
			count++;
		tmp = tmp->next_token;
	}
	return (count);
}

void	filling_cmd_tab_bis(t_tree *branch, int *i, t_token	*tmp)
{
	tmp->parsed = true;
	branch->exec_args[(*i)++] = ft_strdup(tmp->value);
}

//Creates a tab: tab[0] is cmd name, tab[1...] = args/options
void	filling_cmd_tab(t_tree *branch, int size)
{
	t_token	*tmp;
	int		i;

	i = 0;
	tmp = branch->first_token;
	branch->exec_args = malloc(sizeof(char *) * (size + 1));
	if (!branch->exec_args)
		error(2, "Error in allocating cmd tab.\n");
	while (tmp && tmp->index <= branch->end_index)
	{
		if ((tmp->e_tk_type == TK_WORD || tmp->e_tk_type == TK_DOLLAR
				|| tmp->e_tk_type == TK_QUOTE)
			&& (tmp->parsed == false && i == 0))
			filling_cmd_tab_bis(branch, &i, tmp);
		if ((tmp->e_tk_type == TK_WORD || tmp->e_tk_type == TK_EQUAL
				|| tmp->e_tk_type == TK_DOLLAR || tmp->e_tk_type == TK_QUOTE)
			&& (tmp->parsed == false && i > 0))
			filling_cmd_tab_bis(branch, &i, tmp);
		tmp = tmp->next_token;
	}
	branch->exec_args[i] = NULL;
}

//from tab of cmd args (tab[0] being 'cmd name') created in 'filling_cmd_tab',
//fills up exec_name and exec_path for each branch
void	parsing_cmd(t_tree *branch)
{
	int	size;

	size = count_unparsed_word(branch);
	filling_cmd_tab(branch, size);
	if (!branch->exec_args[0])
		branch->exec_name = NULL;
	else
		branch->exec_name = ft_strdup(branch->exec_args[0]);
	branch->exec_path = check_exec_paths(branch->treetop->paths,
			branch->exec_name);
}
