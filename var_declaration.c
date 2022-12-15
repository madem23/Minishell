/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_declaration.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 11:01:37 by antoine           #+#    #+#             */
/*   Updated: 2022/12/15 17:58:21 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expander/expander.h"

int	change_var_value(t_var *list, char *name, char *value)
{
	t_var	*tmp;

	tmp = list;
	while (tmp && ft_strcmp(tmp->name, name))
		tmp = tmp->next;
	if (tmp)
	{
		free(tmp->value);
		tmp->value = value;
		return (1);
	}
	return (0);
}

int	parsing_var_def(t_tree *branch)
{	
	t_token	*tmp;
	char	**v;

	tmp = branch->first_token;
	if (!branch->exec_name && branch->piped_input == false
		&& branch->piped_output == false)
	{
		while (tmp && tmp->index <= branch->end_index)
		{
			if (tmp->e_tk_type == TK_EQUAL)
			{
				v = ft_split(tmp->value, '=');
				v[1] = expander_convert(branch->minishell,
						creating_expander_tree(v[1]));
				if (change_var_value(branch->minishell->var_def, v[0], v[1]))
					return (1);
				else
					var_add_back(&branch->minishell->var_def,
						var_init(ft_strdup(v[0]), ft_strdup(v[1]), false));
			}
			tmp = tmp->next_token;
		}
	}
	return (0);
}
