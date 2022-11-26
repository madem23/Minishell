/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 10:25:12 by antoine           #+#    #+#             */
/*   Updated: 2022/11/26 19:00:11 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "../parser/parser.h"

void	create_var_entry_in_env(char *var_name, t_minishell *minishell)
{
	char	*new_value;
	t_var	*tmp;
	char	*str_tmp;

	new_value = NULL;
	tmp = minishell->var_def;
	while (tmp)
	{
		if (ft_strcmp(var_name, tmp->name) == 0 && tmp->env == false)
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

int	export(t_tree *branch, t_minishell *minishell)
{
	int		i;
	int		modif_status;
	char	**var_def;

	modif_status = 0;
	if (tab_len(branch->exec_args) == 1)
	{
		i = 0;
		while (minishell->envp[i])
			printf("declare -x %s\n", minishell->envp[i++]);
		return (0);
	}
	i = 1;
	while (branch->exec_args[i])
	{
		var_def = ft_split(branch->exec_args[i], '=');
		var_def[1] = parsing_quotes_dollar(var_def[1], branch->minishell, creating_word_parsing_tree(var_def[1], branch->minishell)); 
		if (locate_char(branch->exec_args[i], '=') >= 0)
		{
			if (var_def)
				modif_status = modify_existing_string_var(branch, var_def[0], var_def[1]);
			if (modif_status == 0) //existe encore nulle part, doit etre en plus rajoute dans list
				var_add_back(&branch->minishell->var_def,
					variable_init(ft_strdup(var_def[0]), ft_strdup(var_def[1]), false));
		}
		create_var_entry_in_env(var_def[0], minishell);
		i++;
	}
	return (0);
}
	