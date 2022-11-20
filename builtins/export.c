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
#include "../parser/parser.h"

void	create_var_entry_in_env(char *exec_arg, t_minishell *minishell, int i_equal)
{
	char	*new_value;
	t_var	*tmp;
	char	*str_tmp;

	new_value = NULL;
	tmp = minishell->var_def;
	while (tmp)
	{
		if (ft_strncmp(exec_arg, tmp->name, i_equal) == 0 && tmp->env == false)
		{
			tmp->env = true;
			str_tmp = ft_strjoin(tmp->name, "=");
			new_value = ft_strjoin(str_tmp, tmp->value);
			free(str_tmp);
			minishell->envp = add_str_to_tab(minishell->envp, new_value);
			free(new_value);
			break ;
		}
		tmp = tmp->next;
	}
}

void	export(t_tree *branch, t_minishell *minishell)
{
	int		i;
	int		modif_status;
	int		i_equal;

	modif_status = 0;
	if (tab_len(branch->exec_args) == 1)
	{
		i = 0;
		while (minishell->envp[i])
			printf("declare -x %s\n", minishell->envp[i++]);
		return ;
	}
	i = 1;
	while (branch->exec_args[i])
	{
		i_equal = locate_char(branch->exec_args[i], '=');
		if (i_equal == -1)
			i_equal = ft_strlen(branch->exec_args[i]);
		modif_status = modify_existing_var(branch, branch->exec_args[i], i_equal);
		if (modif_status == 0) //existe encore nulle part, doit etre en plus rajoute dans list
			var_add_back(&branch->minishell->var_def,
				variable_init(ft_substr(branch->exec_args[i], 0, i_equal), ft_strdup(branch->exec_args[i] + i_equal + 1), false));
		create_var_entry_in_env(branch->exec_args[i], minishell, i_equal);
		i++;
	}
} 
	