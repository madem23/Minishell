/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_declaration.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elpolpa <elpolpa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 11:01:37 by antoine           #+#    #+#             */
/*   Updated: 2022/12/22 11:09:05 by elpolpa          ###   ########.fr       */
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
		tmp->value = ft_strdup(value);
		return (1);
	}
	return (0);
}

int	var_declaration(t_tree *branch, char *token_value)
{
	char	**v;
	int		n;

	v = ft_trim_at_char(token_value, '=');
	if (!v[1])
		v[1] = ft_strdup("");
	else
		v[1] = expander_convert(branch->minishell,
				creating_expander_tree(v[1]));
	if (change_var_value(branch->minishell->var_def, v[0], v[1]))
	{
		free_split_var(v);
		return (0);
	}
	else
		var_add_back(&branch->minishell->var_def,
			var_init(ft_strdup(v[0]), ft_strdup(v[1]), false));
	free_split_var(v);
	return (1);
}

int	parsing_var_def(t_tree *branch)
{	
	t_token	*tmp;

	tmp = branch->first_token;
	if (!branch->exec_name && branch->piped_input == false
		&& branch->piped_output == false)
	{
		while (tmp && tmp->index <= branch->end_index)
		{
			if (tmp->e_tk_type == TK_EQUAL)
			{
				if (!var_declaration(branch, tmp->value))
					return (1);
			}
			tmp = tmp->next_token;
		}
	}
	return (0);
}

void	create_var_entry_in_env(char *var_name, t_minishell *minishell)
{
	t_var	*tmp;

	tmp = minishell->var_def;
	while (tmp)
	{
		if (!ft_strcmp(var_name, tmp->name) && tmp->env == false)
		{
			tmp->env = true;
			return ;
		}
		else if (!ft_strcmp(var_name, tmp->name) && tmp->env == true)
			return ;
		tmp = tmp->next;
	}
	if (!tmp)
	{
		var_add_back(&minishell->var_def,
			var_init(ft_strdup(var_name),
				ft_strdup(""), true));
	}
}
