/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 10:25:12 by antoine           #+#    #+#             */
/*   Updated: 2022/11/18 12:05:12 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

//need to clean join

void	is_var_def(char	**args, t_tree* branch)
{
	int	i;

	i = 1;
	while (args[i])
	{
		if (ft_strchr(args[i], '='))
			parsing_var_def(branch);
		i++;
	}
}

void	export(t_tree *branch, t_minishell *minishell)
{
	int		i;
	t_var	*tmp;
	char	*new_value;

	if (tab_len(branch->exec_args) == 1)
	{
		i = 0;
		while (minishell->envp[i])
		{
			printf("declare -x ");
			printf("%s\n", minishell->envp[i]);
			i++;
		}
		return ;
	}
	is_var_def(branch->exec_args, branch);
	i = 1;
	while (branch->exec_args[i])
	{
		tmp = minishell->var_def;
		new_value = NULL;
		while (tmp)
		{
			if (ft_strcmp(branch->exec_args[i], tmp->name) == 0 && tmp->env == false)
			{
				tmp->env = true;
				new_value = ft_strjoin(ft_strjoin(tmp->name, "="), tmp->value);
			}
			tmp = tmp->next;
		}
		if (new_value)
			minishell->envp = add_str_to_tab(minishell->envp, new_value);
		free(new_value);
		i++;
	}
} 
	